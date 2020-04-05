import mysql.connector as mysql



def initialize():
    db = mysql.connect(
        host = "localhost",
        user = "root",
        passwd = "123",
        database = "firsttry"
    )
    return db

def putValueInDatabase(num):
    db = initialize()
    cursor = db.cursor()
    sqlFormula = "INSERT INTO randomNumbers(id,number) VALUES (0,%s)" % num
    #cursor.execute(sqlFormula,num)
    cursor.execute(sqlFormula)
    db.commit()
    cursor.close()
    return 99
    
def getAllValuesFromDatabase():
    

    cursor.execute("SELECT * FROM randomNumbers")

    result = cursor.fetchall()

    values = ""
    for row in result:
        values = values + " " + str(row[0])
    print(values)

    return values


def resetDatabaseTable():

    cursor.execute("TRUNCATE TABLE randomNumbers")

    db.commit()

def close():
    db.close()

#initialize()
#putValueInDatabase(2)
#close()

#putValueInDatabase(5)
#getAllValuesFromDatabase()
#resetDatabaseTable()
#getAllValuesFromDatabase()



    

    

    
    
