// TODO: VERIFY
#include "DBdataGenerator/DBdataGenerator.hpp"
#include "UniversityDB/UniversityDB.hpp"

#include <iostream>

int main()
{
    using university::UniversityDB;
    using university::data_generator::DBdataGenerator;

    UniversityDB data_base;
    DBdataGenerator generator(data_base);

    generator.addStudents(200);
    generator.addEmployees(25);

    data_base.sortByLastName();
    data_base.display();

    std::cout << "###################\n"
              << "Final data base size: " << data_base.size() << std::endl;

    return 0;
}
