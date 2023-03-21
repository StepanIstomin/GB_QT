function createSimpleTable(tx, tableName) {
    const sql =
    'CREATE TABLE IF NOT EXISTS %1 ('.arg(tableName) +
    'contact_id INTEGER PRIMARY KEY,' +
    'first_name TEXT NOT NULL,' +
    'last_name TEXT NOT NULL,' +
    'email TEXT NOT NULL UNIQUE,' +
    'phone TEXT NOT NULL UNIQUE' +
    ');'
    print(sql)
    tx.executeSql(sql)
}
function addContact(tx, tableName, first_name, last_name, email, phone) {
    const sql =
    'INSERT INTO %1 (first_name, last_name, email, phone)'.arg(tableName) +
    'VALUES("%1", "%2", "%3", "%4");'.arg(first_name).arg(last_name).arg(email).arg(phone)
    print(sql)
    tx.executeSql(sql)
}
function readContacts(tx, tableName, model) {
    model.clear()
    const sql = 'SELECT contact_id, first_name, last_name, email, phone FROM %1'.arg(tableName)
    var result = tx.executeSql(sql)
    for (var i = 0; i < result.rows.length;++i){
        model.appendRow({
                        id: result.rows.item(i).contact_id,
                        first_name: result.rows.item(i).first_name,
                        last_name: result.rows.item(i).last_name,
                        email: result.rows.item(i).email,
                        phone: result.rows.item(i).phone
                        })
    }
}
function readEntry(tx, tableName, row) {
    const sql = 'SELECT first_name, last_name, email, phone FROM %1 WHERE contact_id = %2'.arg(tableName).arg(row)
    var result = tx.executeSql(sql)
    updateFirstName.text = result.rows.item(0).first_name
    updateLastName.text = result.rows.item(0).last_name
    updateEmail.text = result.rows.item(0).email
    updatePhone.text = result.rows.item(0).phone
}
function updateEntry(tx, tableName, row){
    const sql =
    'UPDATE %1 SET first_name = "%2", last_name = "%3", email = "%4", phone = "%5" WHERE contact_id = %6'.arg(tableName).arg(updateFirstName.text).arg(updateLastName.text).arg(updateEmail.text).arg(updatePhone.text).arg(row)
    tx.executeSql(sql)
}
