# Table of Contents
- [HashPair](#hash-pair)
- [HashTable](#hash-table)
---

# HashPair Struct {#hash-pair}

## Variables
| Name                 | Description                                                               |
|----------------------|---------------------------------------------------------------------------|
| unsigned int key     | Holds the key a HashTable would use to find the value within its confines |
| unsigned char* value | Holds the character pointer that this HashPair stores.                    |
| unsigned int hashed  | Holds the aforementioned character pointer hashed.                        |

## Constructors
| Name                                                                  | Description                                   |
|-----------------------------------------------------------------------|-----------------------------------------------|
| HashPair()                                                            | Creates an empty HashPair, storing a nullptr. |
| HashPair(unsigned int key, unsigned char* value, unsigned int hashed) | Creates a HashPair with the given values.     |

---

# HashTable Class {#hash-table}

## Constructors
| Name                                                 | Description                                                                              |
|------------------------------------------------------|------------------------------------------------------------------------------------------|
| HashTable(int size = 100)                            | Creates an empty HashTable with the given size.                                          |
| HashTable(std::initializer_list<const char*> values) | Creates a hash table of twice the length of the given initializer list, with the given contents inside. |
| HashTable(const char* values[], int length)          | Creates a hash table of twice the length of the given character pointer array, with the given contents inside. |

## Operators
| Name       | Description                                                                  |
|------------|------------------------------------------------------------------------------|
| operator[] | Returns a reference to the given value, or nullptr if it isn't in the table. |

## Functions
| Name                                    | Description                                                                              |
|-----------------------------------------|------------------------------------------------------------------------------------------|
| bool Add(const char* value)             | Adds the given value to the hash table, and returns whether it was successful or not.    |
| bool Remove(const char* value)          | Removes the given value to the hash table, and returns whether it was successful or not. |
| int Resize(int size)                    | Resizes the hash table to the given size.[^1]                                            |
| bool Contains(char* value)              | Returns true if the given value is contained in the hash table.                          |
| int GetCount()                          | Returns the amount of things stored in the HashTable.                                    |
| int GetArrayLength()                    | Returns the length of the array within the HashTable.                                    |
| unsigned int Hash(unsigned char* value) | Hashes the given character pointer using ELF hash.                                       |
| void Clear()                            | Clears the entire array and reinitializes it.                                            |

[^1]: If the size is smaller than the current count, you will lose data and there is no good way to know what data you lost!
