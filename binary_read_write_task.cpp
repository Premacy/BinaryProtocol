#include <iostream>
#include <cstring>
#include <fstream>

template<typename T>
T* to_bytes(char* bytes){
    T* result = reinterpret_cast<T*>(bytes);
    return result;
}

struct Person{
    double salary;
    char name[50];
    int id;
};

void serealize(const Person& person, const std::string& path){
    //std::fstream file(path, std::ios::binary);
    std::fstream file(path);

    if(!file.is_open()){
        std::cout << "Can no open file" << std::endl;
    }

    char person_bytes[sizeof(person)];
    memcpy(person_bytes, &person, sizeof(person));

    file.write(person_bytes, sizeof(person));
}

bool deserialize(Person& person, const std::string& path){
    std::fstream file(path);

    int id;
    double salary;
    char name[50];

    const std::size_t buffer_size = sizeof(person);
    char read_buffer[buffer_size];

    int read_bytes = file.readsome(read_buffer, buffer_size);
    std::cout << "Read bytes: " << read_bytes << std::endl;

    if(read_bytes != buffer_size){
        std::cout << "Read error" << std::endl;
        return false;
    }

    person = *(reinterpret_cast<Person*>(read_buffer));

    return true;
}

void printPerson(const Person& person){
    std::cout << "Name: " << person.name << std::endl;
    std::cout << "Id: " << person.id << std::endl;
    std::cout << "Salary: " << person.salary << std::endl;
}

void readPersonFromTerminal(Person& person){
    std::cout << "Enter name: " << std::endl;
    std::cin >> person.name;

    std::cout << "Enter id: " << std::endl;
    std::cin >> person.id;

    std::cout << "Enter salary: " << std::endl;
    std::cin >> person.salary;
}

int main(){
    Person person;

    readPersonFromTerminal(person);
    //printPerson(person);

    std::cout << "Serealizing..." << std::endl;
    serealize(person, "test.dat");

    std::cout << "Deserializing..." << std::endl;
    if(!deserialize(person, "test.dat")) {
        //exit(-1);
    }

    printPerson(person);
    return 0;
}
