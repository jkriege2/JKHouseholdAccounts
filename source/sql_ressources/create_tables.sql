CREATE TABLE settings (
        key VARCHAR(100) PRIMARY KEY NOT NULL
      , value VARCHAR(200)
      , type VARCHAR(200)
)

----####----
			   
CREATE TABLE expenses (
        id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
      , date DATE
      , idPayee INTEGER NOT NULL
      , idPayer INTEGER NOT NULL
      , amount MONEY
      , idCategory INTEGER NOT NULL
      , description VARCHAR(200)
)

----####----

CREATE TABLE recurringExpenses (
        id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
      , dateStart DATE
      , repeatMode INTEGER
      , lastExecutedDate DATE
      , idPayee INTEGER NOT NULL
      , idPayer INTEGER NOT NULL
      , amount MONEY
      , idCategory INTEGER NOT NULL
      , description VARCHAR(200)
)

----####----

CREATE TABLE valueables (
        id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
      , name VARCHAR(200)
      , value MONEY
      , category VARCHAR(200)
      , idPayer INTEGER NOT NULL
      , description VARCHAR(200)
      , dateAdded DATE
)


----####----

CREATE TABLE categories (
      id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
    , superCat VARCHAR(200) NOT NULL
    , name VARCHAR(200) NOT NULL
    , fullCat VARCHAR(401) GENERATED ALWAYS AS (superCat || '/' || name) STORED
)

----####----

CREATE TABLE payers (
      id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
    , name VARCHAR(200) NOT NULL
)

----####----

CREATE TABLE payees (
      id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
    , name VARCHAR(200) NOT NULL
    , recentCategoryID INTEGER
)

----####----

CREATE TABLE budgets (
      id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
    , dateAdded DATE
    , name VARCHAR(200)
    , description VARCHAR(200)
)

----####----

CREATE TABLE budgetEntries (
      id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT
    , idBudget INTEGER NOT NULL
    , idCategory INTEGER NOT NULL
    , budget MONEY
    , budgetType INTEGER
)
