#PROJECT ORGANIZATION ON GITHUB

Due to the fact, that UniversityDB was divided in two homework assignments, two dedicated branches on github were organized to enable independent evaluation of state of development:

* universityDB-OOP-basics
* universityDB-OOP-advanced

In order to evaluate the specific task in isolation, please checkout relevant branch from github

##Homework task details for "universityDB-OOP-basics"

All requirements were satisfied with some minor additions.
All testing was realised pury with GTest libraries.

##Homework task details for "universityDB-OOP-advanced"

Main testing was realised using GTest libraries.
One additional layer of testing was provided in the main app, as DBdataGenerator provides random generation, which in nature is problematic to test.
Therefore a database was instantiated in the main app and displayed to prove visually, that genarator works as intended.


#BUILDING

mkdir build
cd build
cmake ..
cmake --build .

#TESTING

After building the project, ensure that you are in the build folder.
Type ```ctest``` to run all tests, or change dir to bin folder and run tests independently.
The main app (university-db-project) can also be run from the main folder and provides additional simple test for defining, generating random data for the base and displaying it.