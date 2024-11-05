//SPDX-License-Identifier: MIT
pragma solidity^0.8.18;
contract StudentData{
    struct Student{
        string name;
        uint256 age;
    }
    Student[] public students;

    function addStudent(string memory _name,uint256 _age)public{
        Student memory newStudent=Student(_name,_age);
        students.push(newStudent);
        emit StudentAdded(_name, _age);
    }
    function getStudentCount() public view returns(uint256){
        return students.length;
    }
    function getStudents(uint256 index)public view returns(string memory,uint256){
        require(index<students.length,"Student does not exist");
        Student memory student=students[index];
        return (student.name,student.age);
    }

 // fallback function is executed when a contract receives Ether along with a call to a function that does not exist or with incorrect parameters
    // make this function payable if there are Ether transactions
    fallback() external {
        revert("Invalid function call or Ether transfer not supported.");   
    }

    // to trigger the fallback function in Remix IDE:
    // scroll to the bottom of the deployed contracts tab and expand your contract
    // in the CALLDATA input field type: 0x12345678
    // click on TRANSACT, and check the terminal for reverted output
}
