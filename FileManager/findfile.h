#ifndef FINDFILE_H
#define FINDFILE_H

#include <QWidget>
#include <QProgressDialog>
#include <QFileDialog>
#include <QTextStream>      //Использует операторы потока для чтения файла
#include <QTableWidget>     //Просмотр результатов поиска в таблице
#include <QDesktopServices> //Открывает файлы в списке результатов в подходящем приложении
#include <QComboBox>
#include <QShortcut>
#include <QAbstractButton>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QApplication>
#include <QDirIterator>
#include <QMimeDatabase>
#include <QMimeType>
#include <QHeaderView>
#include <QMenu>
#include <QClipboard>
#include <QThread>
#include <QDebug>

// Класс с кодом выполнения продолжительной операции для помещения в отдельный поток
class Worker : public QObject
{
  Q_OBJECT
public:
  explicit Worker(QObject* parent = nullptr);
  ~Worker();
    QStringList getFiles();
    void find(const QString &fileName, const QString &text, const QString &path);
public slots:
signals:
private:
    QStringList findFiles(const QStringList &files, const QString &text);
    QStringList files;
};



class FindFile : public QWidget
{
    Q_OBJECT
public:
    explicit FindFile(QWidget *parent = nullptr);
private slots:
    void browse();
    void find();
    void openFileOfItem(int row, int column);
    void contextMenu(const QPoint &pos);

private:
    QStringList findFiles(const QStringList &files, const QString &text);
    void showFiles(const QStringList &paths);
    QComboBox *createComboBox(const QString &text = QString());
    void createFilesTable();

    QComboBox *fileComboBox;
    QComboBox *textComboBox;
    QComboBox *directoryComboBox;
    QLabel *filesFoundLabel;
    QPushButton *findButton;
    QTableWidget *filesTable;
    QDir currentDir;
    Worker *worker;     //Рабочий объект
    QThread *findThread;//Объект класса QThread позволяет выполнять код в отдельном потоке
};

#endif // FINDFILE_H
