# CSC541_assgn1

Advanced Data Structures


We are given 2 files seek.db and keys.db (values in sorted order), we need to findout whether values in seek.db exist in the key (hit) or they don't (miss).

We compare the time required to do:
a)disk based sequential search - involves reading values from file when required
b)disk based binary search - involved moving around a file with sorted keys using binary search
c)In memory sequential search - involves storing the file in main memory and searching for values
d)In memory binary search - involves storing the file in memory and performing binary search to search for values
