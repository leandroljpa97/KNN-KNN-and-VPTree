
::redWine dataset -> NUMERICAL DATASET. It will be written in Results/KNN_NUMERICAL_K= X...
:: -----------------------------------------------------------
:: KNN -> Leave-One-Out Method to redWine, and different K values
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 1
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 3
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 4
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 5
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 6
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 7
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 10
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 13
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 15
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 19
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 23
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 25


:: KNN+ -> Leave-One-Out Method to redWine, and different K values
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 1
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 3
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 4
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 5
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 6
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 7
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 10
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 13
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 15
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 19
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 23
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 25

::            NORMALIZATION
::Using Normalize data KNN and KNN+ -> Leave-One out
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 2 -k 12 -n 
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 2 -k 12 -n

::Using 1/3 of Random samples from the data set (-c 1) 
::and Normalize data KNN and KNN+ -> Leave-One out
main.exe -a 0 -f DataSets/redWine.txt -t 0 -c 1 -k 8 -n 
main.exe -a 1 -f DataSets/redWine.txt -t 0 -c 1 -k 8 -n
::----------------------------------------------------------------------------



pause