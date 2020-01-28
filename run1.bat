
::iris dataset -> NUMERICAL DATASET. It will be written in Results/KNN_NUMERICAL_K= X...
:: -----------------------------------------------------------
:: KNN -> Leave-One-Out Method to iris, and different K values
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 1
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 3
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 4
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 5
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 6
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 7
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 10
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 13
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 15
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 19
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 23
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 25


:: KNN+ -> Leave-One-Out Method to iris, and different K values
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 1
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 3
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 4
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 5
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 6
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 7
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 10
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 13
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 15
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 19
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 23
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 25

::            NORMALIZATION
::Using Normalize data KNN and KNN+ -> Leave-One out
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 2 -k 12 -n 
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 2 -k 12 -n

::Using 1/3 of Random samples from the data set (-c 1) 
::and Normalize data KNN and KNN+ -> Leave-One out
main.exe -a 0 -f DataSets/iris.txt -t 0 -c 1 -k 8 -n 
main.exe -a 1 -f DataSets/iris.txt -t 0 -c 1 -k 8 -n
::----------------------------------------------------------------------------


::Example with the user choosing to classify only sample number 0 (-c 0 0 ) - KNN and KNN+ 
main.exe -a 0 -f DataSets/teste.txt -t 0 -c 0 0 -k 2
main.exe -a 1 -f DataSets/teste.txt -t 0 -c 0 0 -k 2

::Example where the samples to be classified are out of the dataset (are not part of the dataset)
:: (-c 3 trainingsetName)
main.exe -a 0 -f DataSets/teste.txt -t 0 -c 3 testset/test.txt -k 3


::Example with mixed data set (numerical + categoric) 
::Classify sample number 0 of the categNumTeste dataSet with KNN and KNN+
main.exe -a 0 -f DataSets/categNumTeste.txt -t 1 -c 0 0 -k 2
main.exe -a 1 -f DataSets/categNumTeste.txt -t 1 -c 0 0 -k 2




::car dataset -> mixed DATASET. It will be written in Results/KNN_CATEGORIC_K= X...
:: -----------------------------------------------------------
:: KNN -> Leave-One-Out Method to iris, and different K values
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 1
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 3
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 4
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 5
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 6
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 7
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 10
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 13
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 15
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 19
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 23
main.exe -a 0 -f DataSets/car.txt -t 1 -c 2 -k 25


:: KNN+ -> Leave-One-Out Method to iris, and different K values
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 1
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 3
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 4
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 5
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 6
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 7
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 10
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 13
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 15
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 19
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 23
main.exe -a 1 -f DataSets/car.txt -t 1 -c 2 -k 25



::Using 1/3 of Random samples from the data set (-c 1) 
::and Normalize data KNN and KNN+ -> Leave-One out
main.exe -a 0 -f DataSets/car.txt -t 1 -c 1 -k 8 -n 
main.exe -a 1 -f DataSets/car.txt -t 1 -c 1 -k 8 -n
::----------------------------------------------------------------------------


pause