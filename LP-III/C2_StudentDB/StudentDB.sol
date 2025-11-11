// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

// Write a program in solidity to create Student data. Use the following constructs: 
// a. Structures 
// b. Arrays 
// c. Fallback

contract StudentDB  {
    // Define a structure to hold student details
    struct Student {
        string name;
        uint256 roll;
        uint256 age;
        string class;
    }

    Student[] public students;
    mapping(uint256 => bool) private rollExists; 

    // Event to log student data when added
    event StudentAdded(string name, uint256 rollNumber);

    // Event to log Ether received in the fallback function
    event FallbackCalled(address sender, uint256 amount, string message);

    function addStudent(
        string calldata _name,
        uint256 _roll,
        uint256 _age,
        string calldata _class
    ) public {
        require(bytes(_name).length > 0, "Name cannot be blank");
        require(bytes(_class).length > 0, "Class cannot be blank");
        require(_age > 0 && _age < 100, "Invalid Age Field");
        require(!rollExists[_roll], "Student roll number already exists");
        Student memory newStudent = Student({
            name: _name,
            roll: _roll,
            age: _age,
            class: _class
        });

        students.push(newStudent);
        rollExists[_roll] = true;
        emit StudentAdded(_name, _roll);
    }


    function getTotalStudents() public view returns (uint256) {
        return students.length;
    }   

    function getStudent(uint256 index) public view returns (string memory, uint256, uint256, string memory) {
        require(index < students.length, "Invalid index");
        Student memory student = students[index];
        return (student.name, student.roll, student.age, student.class);
    }

    // Fallback function
    fallback() external payable {
        emit FallbackCalled(msg.sender, msg.value, "Fallback function called");
    }

    // receive Ether directly (without data)
    receive() external payable {
        emit FallbackCalled(msg.sender, msg.value, "Ether received via receive()");
    }
}
