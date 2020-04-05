import mysql.connector as mysql


def initialize():
    db = mysql.connect(
        host="localhost",
        user="root",
        passwd="123",
        database="firsttry"
    )
    return db


def putValueInDatabase(num):
    db = initialize()
    cursor = db.cursor()
    sqlFormula = "INSERT INTO randomNumbers(id,number) VALUES (0,%s)" % num
    cursor.execute(sqlFormula)
    db.commit()
    cursor.close()
    db.close()
    return 99


def getAllValuesFromDatabase(num):
    db = initialize()
    cursor = db.cursor()

    cursor.execute("SELECT number FROM randomNumbers")

    result = cursor.fetchall()

    values = ""
    for row in result:
        values = values + " " + str(row[0])

    f = open("files/results.txt", "w")
    f.write("----------------\n")
    f.write(values)
    f.close()
    cursor.close()

    db.close()
    return values


def resetDatabaseTable(test):
    db = initialize()
    cursor = db.cursor()

    cursor.execute("TRUNCATE TABLE randomNumbers")

    db.commit()

    db.close

    return 99


def close():
    db.close()
