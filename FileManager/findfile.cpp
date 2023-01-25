#include "findfile.h"

FindFile::FindFile(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle(tr("Find Files"));
    QPushButton *browseButton = new QPushButton(tr("&Browse..."), this);        // Кнопка выбора папки
    connect(browseButton, &QAbstractButton::clicked, this, &FindFile::browse);
    findButton = new QPushButton(tr("&Find"), this);                            // Кнопка поиска
    connect(findButton, &QAbstractButton::clicked, this, &FindFile::find);

    fileComboBox = createComboBox(tr("*"));
    textComboBox = createComboBox();
    directoryComboBox = createComboBox(QDir::toNativeSeparators(QDir::currentPath()));

    filesFoundLabel = new QLabel;

    createFilesTable();

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(new QLabel(tr("Named:")), 0, 0);
    mainLayout->addWidget(fileComboBox, 0, 1, 1, 2);
    mainLayout->addWidget(new QLabel(tr("Containing text:")), 1, 0);
    mainLayout->addWidget(textComboBox, 1, 1, 1, 2);
    mainLayout->addWidget(new QLabel(tr("In directory:")), 2, 0);
    mainLayout->addWidget(directoryComboBox, 2, 1);
    mainLayout->addWidget(browseButton, 2, 2);
    mainLayout->addWidget(filesTable, 3, 0, 1, 3);
    mainLayout->addWidget(filesFoundLabel, 4, 0, 1, 2);
    mainLayout->addWidget(findButton, 4, 2);

    findThread = new QThread(this);  //создание "объекта потока"
    worker = new Worker(); //без this, т.к. объекту запрещено указывать родителя
    worker->moveToThread(findThread); //"перенос" рабочего объекта из основного потока в поток объекта thread
    findThread->start(QThread::LowPriority); //запуск отдельного потока
    connect(this, SIGNAL(destroyed()), findThread, SLOT(quit())); //завершение потока при удалении объекта виджета поиска

    connect(new QShortcut(QKeySequence::Quit, this), &QShortcut::activated, qApp, &QApplication::quit);
    //Поскольку мы создаем QShortcut с помощью QKeySequence::Quit и подключаем его к QApplication::quit(),
    //на большинстве платформ можно будет нажать Control-Q для выхода (или любую другую стандартную клавишу выхода, настроенную на этой платформе)

    filesTable->setContextMenuPolicy(Qt::CustomContextMenu);
    // устанавливаем политику контекстного меню табличного представления на Qt::CustomContextMenu
    // и подключаем слот contextMenu() к его сигналу customContextMenuRequested()
    connect(filesTable, &QTableWidget::customContextMenuRequested, this, &FindFile::contextMenu);

    // получаем абсолютное имя файла из данных QTableWidgetItem и заполняем контекстное меню действиями,
    // предлагающими скопировать имя файла и открыть файл.
    connect(filesTable, &QTableWidget::cellActivated, this, &FindFile::openFileOfItem);
}

// представляет пользователю диалоговое окно с файлом, используя класс QFileDialog
void FindFile::browse()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath())); //QFileDialog::getExistingDirectory возвращает существующий каталог, выбранный пользователем.
    if (!directory.isEmpty()) {
        if (directoryComboBox->findText(directory) == -1)
            directoryComboBox->addItem(directory);  //отображаем каталог в directorycombobox
        directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory)); //обновляем текущий индекс.
    }
}


void FindFile::find() // вызывается всякий раз, когда пользователь запрашивает новый поиск нажатием кнопки Find.
{
    qDebug() << "Запуск FindFile::find()";
    filesTable->setRowCount(0); //исключаем все предыдущие результаты поиска, установив количество строк виджетов таблицы равным нулю

    QString fileName = fileComboBox->currentText();                     // извлекаем указанное имя файла
    QString text = textComboBox->currentText();                         // текст
    QString path = QDir::cleanPath(directoryComboBox->currentText());   // и путь к каталогу из соответствующих полей
    currentDir = QDir(path); //используем путь к каталогу для создания QDir; класс QDir предоставляет доступ к структуре каталога и его содержимому.
    /*QStringList filter;
    if (!fileName.isEmpty())
        filter << fileName;
    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories); //используем QDirIterator для перебора файлов, соответствующих указанному имени файла,
    */
    QStringList files;                                                                                                      //  и создания QStringList путей.
    worker->find(fileName, text, path);
    files = worker->getFiles();
    /*while (it.hasNext()) //выполняем поиск по всем файлам в списке, используя функцию findFiles(), удаляя те, которые не содержат указанного текста.
        files << it.next();
    if (!text.isEmpty())
        //files = findFiles(files, text); // вариант без дополнительного worker'a
    */
    files.sort();
    showFiles(files);
}

// Обе функции findFiles() и showFiles() вызываются из слота find().

//выполняем поиск по списку файлов, ища те, которые содержат указанный текст.
//это может быть очень медленной операцией в зависимости от количества файлов, а также их размеров.
QStringList FindFile::findFiles(const QStringList &files, const QString &text) //выполняем поиск по списку файлов, ища те, которые содержат указанный текст.
{
    //QProgressDialog отображает диалоговое окно выполнения, если приложению приходится выполнять поиск по большому количеству файлов или если некоторые из файлов имеют большой размер.
    //QProgressDialog также может позволить пользователю прервать операцию, если она занимает слишком много времени.
    QProgressDialog progressDialog(this);

    progressDialog.setCancelButtonText(tr("&Cancel"));
    progressDialog.setRange(0, files.size());
    progressDialog.setWindowTitle(tr("Find Files"));
    QMimeDatabase mimeDatabase;
    QStringList foundFiles;

    //Мы просматриваем файлы по одному за раз, и для каждого файла мы обновляем значение QProgressDialog.
    //Это свойство содержит текущую сумму достигнутого прогресса. Также обновляем метку диалогового окна прогресса.

    for (int i = 0; i < files.size(); ++i) {
        progressDialog.setValue(i);
        progressDialog.setLabelText(tr("Searching file number %1 of %n...", nullptr, files.size()).arg(i));
        // Вызываем функцию QCoreApplication::processEvents(), используя объект QApplication.
        // Таким образом, мы чередуем отображение достигнутого прогресса с процессом поиска по файлам, чтобы приложение не выглядело замороженным.
        // QCoreApplication::processEvents() обрабатывает все ожидающие события в соответствии с указанными QEventLoop::ProcessEventFlags до тех пор,
        // пока больше не останется событий для обработки. Флаги по умолчанию - QEventLoop::AllEvents.
        QCoreApplication::processEvents();
        const QString fileName = files.at(i);
        const QMimeType mimeType = mimeDatabase.mimeTypeForFile(fileName);
        if (mimeType.isValid() && !mimeType.inherits(QStringLiteral("text/plain"))) {
          qWarning() << "Not searching binary file " << QDir::toNativeSeparators(fileName);
          continue;
        }
                                                //После обновления QProgressDialog
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {   // мы открываем файл в режиме только для чтения и читаем по одной строке за раз,
            QString line;
            QTextStream in(&file);              // используя QTextStream.
            while (!in.atEnd()) {
                if (progressDialog.wasCanceled())               // Для каждой прочитанной строки мы проверяем, был ли отменен QProgressDialog.
                  break;                                        // Если это так, мы прерываем операцию,
                line = in.readLine();
                if (line.contains(text, Qt::CaseInsensitive)) { // в противном случае проверяем, содержит ли строка указанный текст.
                  foundFiles << files[i];                       // Когда находим текст в одном из файлов, добавляем имя файла в список найденных файлов, содержащих указанный текст
                  break;
                }
            }
        }
    }
    return foundFiles;                          // возвращаем список найденных файлов.
}

enum { absoluteFileNameRole = Qt::UserRole + 1 };

// просматриваем предоставленный список имен файлов,
// добавляя каждое относительное имя файла в первый столбец виджета таблицы
// Для последующего использования мы задаем абсолютный путь в качестве данных в QTableWidget, используя роль absoluteFileNameRole, определенную как Qt::UserRole + 1.
void FindFile::showFiles(const QStringList &paths)
{
    for (const QString &filePath : paths) {
        const QString toolTip = QDir::toNativeSeparators(filePath);
        const QString relativePath = QDir::toNativeSeparators(currentDir.relativeFilePath(filePath));
        const qint64 size = QFileInfo(filePath).size();         // извлекаем размер файла, используя QFileInfo (для второго столбца).
        QTableWidgetItem *fileNameItem = new QTableWidgetItem(relativePath);
        fileNameItem->setData(absoluteFileNameRole, QVariant(filePath));
        fileNameItem->setToolTip(toolTip);
        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *sizeItem = new QTableWidgetItem(QLocale().formattedDataSize(size)); // используем QLocale().formattedDataSize(size) для форматирования размера файла в удобочитаемой форме
        sizeItem->setData(absoluteFileNameRole, QVariant(filePath));
        sizeItem->setToolTip(toolTip);
        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);  // первый столбец - относительное имя файла
        filesTable->setItem(row, 1, sizeItem);      // второй столбец - размер
    }
    filesFoundLabel->setText(tr("%n file(s) found (Double click on a file to open it)", nullptr, paths.size()));
    filesFoundLabel->setWordWrap(true);
}



static inline QString fileNameOfItem(const QTableWidgetItem *item) // позволяет получить название элемента
{
    return item->data(absoluteFileNameRole).toString();
}

// вызывается из конструктора, создаем QComboBox с заданным текстом и делаем его доступным для редактирования
// Когда пользователь вводит новую строку в редактируемом поле со списком, виджет может вставлять или не вставлять ее,
// и он может вставить ее в нескольких местах, в зависимости от QComboBox::InsertPolicy. Политика по умолчанию - это QComboBox::InsertAtBottom.
QComboBox *FindFile::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);                                                    // добавляем предоставленный текст в поле со списком
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);    // и указываем политику размера виджета, прежде чем
    return comboBox;                                                            // возвращать указатель на поле со списком.
}


void FindFile::createFilesTable()               // Приватная функция createFilesTable() вызывается из конструктора.
{
    filesTable = new QTableWidget(0, 2);                                            // В этой функции создаем QTableWidget, который будет отображать результаты поиска.
    filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList labels;
    labels << tr("Filename") << tr("Size");
    filesTable->setHorizontalHeaderLabels(labels);                                  // устанавливаем его горизонтальные заголовки
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);  // и режим их изменения размера.
    // Функция QTableView::horizontalHeader() возвращает горизонтальный заголовок табличного представления как QHeaderView.
    // Класс QHeaderView предоставляет строку заголовка или столбец заголовка для представлений элементов,
    // а функция QHeaderView::setResizeMode() устанавливает ограничения на то, как можно изменить размер раздела в заголовке.
    filesTable->verticalHeader()->hide();   // скрываем вертикальные заголовки QTableWidget, используя функцию QWidget::hide(),
    filesTable->setShowGrid(false);         // и удаляем сетку по умолчанию, нарисованную для таблицы, используя функцию QTableView::setShowGrid().
    filesTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(filesTable, &QTableWidget::customContextMenuRequested,
            this, &FindFile::contextMenu);
    connect(filesTable, &QTableWidget::cellActivated,
            this, &FindFile::openFileOfItem);
}

static inline void openFile(const QString &fileName)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));   // QDesktopServices::openUrl() знает, как открыть файл с заданным именем.
}

void FindFile::openFileOfItem(int row, int /* column */)        // Слот openFileOfItem() вызывается, когда пользователь дважды щелкает ячейку в таблице.
{
    const QTableWidgetItem *item = filesTable->item(row, 0);
    openFile(fileNameOfItem(item));
}

void FindFile::contextMenu(const QPoint &pos)
{
   const QTableWidgetItem *item = filesTable->itemAt(pos);
   if (!item)
       return;
   QMenu menu;
#ifndef QT_NO_CLIPBOARD
   QAction *copyAction = menu.addAction("Copy Name");
#endif
   QAction *openAction = menu.addAction("Open");
   QAction *action = menu.exec(filesTable->mapToGlobal(pos));
   if (!action)
       return;
   const QString fileName = fileNameOfItem(item);
   if (action == openAction)
       openFile(fileName);
#ifndef QT_NO_CLIPBOARD
   else if (action == copyAction)
       QGuiApplication::clipboard()->setText(QDir::toNativeSeparators(fileName));
#endif
}

Worker::Worker(QObject *parent) : QObject(parent)
{
}
Worker::~Worker()
{
}

QStringList Worker::getFiles()
{
    return files;
}

void Worker::find(const QString &fileName, const QString &text, const QString &path)
{
    qDebug() << "Worker::find";
    _sleep(5000); // Для проверки 'подвисания' процесса
    QStringList filter;
    if (!fileName.isEmpty())
        filter << fileName;
    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories); //используем QDirIterator для перебора файлов, соответствующих указанному имени файла,
    QStringList files;
    while (it.hasNext())
        files << it.next();
    if (!text.isEmpty())
        files = findFiles(files, text);
}

QStringList Worker::findFiles(const QStringList &files, const QString &text)
{
    qDebug() << "Выполняется Worker findFiles";
    QMimeDatabase mimeDatabase;
    QStringList foundFiles;

    for (int i = 0; i < files.size(); ++i) {
        QCoreApplication::processEvents();
        const QString fileName = files.at(i);
        const QMimeType mimeType = mimeDatabase.mimeTypeForFile(fileName);
        if (mimeType.isValid() && !mimeType.inherits(QStringLiteral("text/plain"))) {
          qWarning() << "Not searching binary file " << QDir::toNativeSeparators(fileName);
          continue;
        }
                                                //После обновления QProgressDialog
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {   // мы открываем файл в режиме только для чтения и читаем по одной строке за раз,
            QString line;
            QTextStream in(&file);              // используя QTextStream.
            while (!in.atEnd()) {
                //if (progressDialog.wasCanceled())               // Для каждой прочитанной строки мы проверяем, был ли отменен QProgressDialog.
                //  break;                                        // Если это так, мы прерываем операцию,
                line = in.readLine();
                if (line.contains(text, Qt::CaseInsensitive)) { // в противном случае проверяем, содержит ли строка указанный текст.
                  foundFiles << files[i];                       // Когда находим текст в одном из файлов, добавляем имя файла в список найденных файлов, содержащих указанный текст
                  break;
                }
            }
        }
    }
    return foundFiles;
}
