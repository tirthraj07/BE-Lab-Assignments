# Assignment 3

## Title
Write a smart contract on a test network, for Bank account of a customer for following
operations:
- Deposit money
- Withdraw Money
- Show balance


## Pre-Requisites

# 🧠 PART 1: Solidity Overview

Solidity is a **statically typed**, **contract-oriented** language used for writing smart contracts that run on the **Ethereum Virtual Machine (EVM)**.

It looks similar to JavaScript or C++, but it has special rules because code runs in a blockchain environment.

Each “program” is called a **contract**, and once deployed on the blockchain, it **cannot be changed**.

---

# 🧩 PART 2: Basic Contract Structure

Here’s the skeleton of any Solidity file:

```solidity
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract MyFirstContract {
    // 1️⃣ State Variables (stored on blockchain)
    uint public count;

    // 2️⃣ Constructor (runs once at deployment)
    constructor() {
        count = 0;
    }

    // 3️⃣ Functions (can be called by users)
    function increment() public {
        count += 1;
    }
}
```

---

# 📘 PART 3: Keywords and Syntax Elements

## 1️⃣ License Identifier

```solidity
// SPDX-License-Identifier: MIT
```

* A comment that specifies the license (required by Solidity compilers now).
* Doesn’t affect logic.

---

## 2️⃣ Pragma

```solidity
pragma solidity ^0.8.0;
```

* Tells compiler which Solidity version to use.
* `^0.8.0` means: use version 0.8.0 **or higher**, but not 0.9.x.

---

## 3️⃣ Contract Declaration

```solidity
contract MyContract {
    // code
}
```

* `contract` is like a **class** in Java.
* Each deployed contract has its own address and storage on the blockchain.

---

# 🧮 PART 4: Data Types

Solidity has several basic types:

### Numeric Types

```solidity
uint myNumber = 5;      // unsigned integer (0 or positive)
int negative = -10;     // signed integer
uint256 bigNumber = 2**256 - 1;
```

`uint` = `uint256` by default (0 to 2²⁵⁶−1).
You can also use `uint8`, `uint16`, `uint32`, etc.

---

### Boolean

```solidity
bool isActive = true;
```

---

### Address

```solidity
address myWallet = 0xAb8483F64d9C6d1EcF9b849Ae677dD3315835cb2;
```

* Represents an Ethereum account or contract address (20 bytes).

---

### String and Bytes

```solidity
string name = "Tirthraj";
bytes32 fixedBytes = "HelloWorld";
```

* Strings are variable-length text.
* `bytes`/`bytes32` are fixed-size byte arrays (used for optimization).

---

### Arrays

```solidity
uint[] numbers;            // dynamic array
uint[5] fixedNumbers;      // fixed-size array
```

---

### Mappings

Mappings are like hashmaps (key-value pairs).

```solidity
mapping(address => uint) public balances;
```

Example usage:

```solidity
balances[msg.sender] = 100; // store
uint myBalance = balances[msg.sender]; // retrieve
```

---

### Structs

You can define custom data types.

```solidity
struct Student {
    string name;
    uint age;
}

Student public s1 = Student("Alice", 20);
```

---

# 🏗️ PART 5: State vs Local vs Global Variables

| Type                | Description                             | Example                         |
| ------------------- | --------------------------------------- | ------------------------------- |
| **State Variable**  | Stored permanently on the blockchain.   | `uint public count;`            |
| **Local Variable**  | Lives only while the function executes. | `uint temp = 5;`                |
| **Global Variable** | Provided by Ethereum environment.       | `msg.sender`, `block.timestamp` |

---

# ⚙️ PART 6: Functions

## 1️⃣ Defining Functions

```solidity
function add(uint a, uint b) public pure returns (uint) {
    return a + b;
}
```

**Function parts:**

```
function <name>(<params>) <visibility> <mutability> returns (<type>)
```

---

## 2️⃣ Function Visibility

| Keyword      | Who can call it                    | Description                         |
| ------------ | ---------------------------------- | ----------------------------------- |
| **public**   | Anyone (including other contracts) | Default for most functions          |
| **private**  | Only inside this contract          | Not visible outside                 |
| **internal** | Inside this and derived contracts  | Like `protected`                    |
| **external** | Only from outside the contract     | More gas-efficient for public calls |

Example:

```solidity
function internalFunc() internal { ... }
function privateFunc() private { ... }
function externalFunc() external { ... }
```

---

## 3️⃣ Function Mutability (State Access)

| Keyword     | Meaning                                                |
| ----------- | ------------------------------------------------------ |
| **view**    | Reads blockchain state, doesn’t modify it.             |
| **pure**    | Doesn’t read or modify state (only local computation). |
| **payable** | Can receive Ether.                                     |

Examples:

```solidity
function getCount() public view returns (uint) {
    return count;
}

function add(uint a, uint b) public pure returns (uint) {
    return a + b;
}

function deposit() public payable {
    // can receive Ether
}
```

---

# 🛡️ PART 7: Control Structures

Same as most languages — `if`, `else`, `for`, `while`.

```solidity
if (balance > 0) {
    balance -= 1;
}

for (uint i = 0; i < 10; i++) {
    // loop logic
}
```

No `break`/`continue` allowed in some contexts (gas limits apply).

---

# ⚖️ PART 8: `require`, `assert`, and `revert`

* `require()` → for user input / access validation
* `assert()` → for internal consistency (should never fail)
* `revert()` → manually trigger a failure

Example:

```solidity
require(msg.value > 0, "Must send ETH");
assert(balance >= 0);
if (errorCondition) revert("Something went wrong");
```

---

# 🧩 PART 9: Modifiers

Modifiers add conditions to functions.

Example:

```solidity
address public owner;

modifier onlyOwner() {
    require(msg.sender == owner, "Not the owner");
    _;
}

function withdraw() public onlyOwner {
    // only owner can call this
}
```

`_` means “continue execution of the original function here”.

---

# 🔔 PART 10: Events

Used to log data that UIs and off-chain apps can listen to.

```solidity
event Deposited(address indexed from, uint amount);

function deposit() public payable {
    emit Deposited(msg.sender, msg.value);
}
```

Events are *not stored in state* — they’re in blockchain logs.

---

# 💸 PART 11: Sending & Receiving Ether

There are 3 main ways:

### 1️⃣ `transfer`

```solidity
payable(receiver).transfer(1 ether);
```

* Simple
* Reverts automatically on failure
* Forwards **2300 gas** only

### 2️⃣ `send`

```solidity
bool success = payable(receiver).send(1 ether);
require(success, "Send failed");
```

* Similar to `transfer` but returns a boolean
* Not recommended (old style)

### 3️⃣ `call` — **modern best practice**

```solidity
(bool sent, ) = payable(receiver).call{value: 1 ether}("");
require(sent, "Call failed");
```

---

# 📦 PART 12: Special Functions

### `constructor`

Runs once at deployment.

```solidity
constructor() {
    owner = msg.sender;
}
```

### `receive()` and `fallback()`

Handle raw Ether transfers.

```solidity
receive() external payable {
    // called when plain ETH is sent
}

fallback() external payable {
    // called when unknown function is called
}
```

---

# ⚡ PART 13: Global Variables (Ethereum Context)

| Variable                | Description                       |
| ----------------------- | --------------------------------- |
| `msg.sender`            | Caller’s address                  |
| `msg.value`             | Amount of wei sent                |
| `block.timestamp`       | Current block time (UNIX seconds) |
| `block.number`          | Current block number              |
| `address(this)`         | The contract’s own address        |
| `address(this).balance` | Contract’s actual ETH balance     |

---

# 🧱 PART 14: Storage vs Memory

| Keyword    | Location                  | Lifetime                   | Example Use                       |
| ---------- | ------------------------- | -------------------------- | --------------------------------- |
| `storage`  | Blockchain                | Permanent                  | State vars                        |
| `memory`   | Temporary (function call) | Lost after call            | Function parameters               |
| `calldata` | Read-only input           | Cheaper for external calls | Function params in external funcs |

Example:

```solidity
function changeName(string memory _name) public {
    name = _name;  // name is storage, _name is memory
}
```

---

# 🧩 PART 15: Inheritance (Optional, Advanced)

Solidity supports contract inheritance like OOP.

```solidity
contract A {
    function greet() public pure returns (string memory) {
        return "Hello";
    }
}

contract B is A {
    function greetWorld() public pure returns (string memory) {
        return string(abi.encodePacked(greet(), " World"));
    }
}
```

---

# ✅ TL;DR — Syntax Summary

| Concept     | Example                                     | Notes               |
| ----------- | ------------------------------------------- | ------------------- |
| Contract    | `contract Bank {}`                          | Main building block |
| Variable    | `uint balance;`                             | Stores data         |
| Function    | `function f() public {}`                    | Defines logic       |
| Modifier    | `modifier onlyOwner() { require(...); _; }` | Restricts access    |
| Event       | `event Log(address user);`                  | Logs info           |
| require     | `require(x>0,"fail");`                      | Validation          |
| payable     | `function deposit() public payable {}`      | Accepts ETH         |
| msg.sender  | `msg.sender`                                | Caller              |
| msg.value   | `msg.value`                                 | Ether sent          |
| transfer    | `.transfer(amount)`                         | Send ETH            |
| call        | `.call{value:amount}("")`                   | Flexible send       |
| constructor | `constructor() {}`                          | Runs on deploy      |

---


## Steps

1. Go to [Remix IDE](https://remix.ethereum.org/).

    ![image](https://github.com/user-attachments/assets/473734af-7376-4c8a-b554-ef083c1e63ed)

2. In the "File Explorer" tab, click the + icon to create a new file. Name the file `Bank.sol`.

    ![image](https://github.com/user-attachments/assets/ac5fb0cd-324f-4066-849c-e5326b8a3c57)

3. Copy the following code into the file

    ```sol
    // SPDX-License-Identifier: MIT
    pragma solidity ^0.8.0;
    
    contract BankAccount {
        address public owner;
        uint256 private balance;
    
        event Deposit(address indexed account, uint256 amount);
        event Withdrawal(address indexed account, uint256 amount);
    
        constructor() {
            owner = msg.sender;
            balance = 0;
        }
    
        modifier onlyOwner() {
            require(msg.sender == owner, "Only the owner can perform this action");
            _;
        }
    
        function deposit() public payable {
            require(msg.value > 0, "Deposit amount must be greater than 0");
            balance += msg.value;
            emit Deposit(msg.sender, msg.value);
        }
    
        function withdraw(uint256 amount) public onlyOwner {
            require(amount > 0, "Withdrawal amount must be greater than 0");
            require(amount <= balance, "Insufficient funds");
            balance -= amount;
            payable(owner).transfer(amount);
            emit Withdrawal(msg.sender, amount);
        }
    
        function getBalance() public view returns (uint256) {
            return balance;
        }
    }
    ```

4. In the left sidebar, click on the Solidity Compiler (the "Compile" tab). Ensure the compiler version is set to `0.8.0` or higher (since we're using `^0.8.0` in the contract).
    
    ![image](https://github.com/user-attachments/assets/f885e83f-1dd1-4642-ad5b-4230ad034c22)
    
    Click the Compile Bank.sol button. If there are no errors, the contract will compile successfully.

5. In the left sidebar, click on the Deploy & Run Transactions tab.

    Set the Environment to Injected Provider. This will connect Remix to MetaMask.
    
    ![image](https://github.com/user-attachments/assets/1ba306fd-42ea-4c4d-b0c5-642ff61c66b0)

    When selected, it will open Metamask and prompt you to connect your account. Make sure you connect the TestNet account only. (I'm currently connected to Sepolia.)

    To get test ETH for your account, go [here](https://cloud.google.com/application/web3/faucet/ethereum/sepolia) to claim 0.05 ETH for free from Google.

    Or you can test it out on the Remix VM itself.

    ![image](https://github.com/user-attachments/assets/3add782c-ca61-419c-b260-53bf8ea322a5)

    Hit Deploy to deploy the contract. Metamask will open to confirm the same.
   
    ![image](https://github.com/user-attachments/assets/5cc574c1-c7ba-4fae-861d-271e957f678b)

7. Interact with the Contract

   Once deployed, you'll see the contract under the "Deployed Contracts" section.

   ![image](https://github.com/user-attachments/assets/0ea27c2f-cfef-4f1d-973b-e942133b32c4)

   You can now interact with the contract using the following functions:
   - Deposit: To deposit Ether, enter an amount in the "Value" field (in ETH), and click deposit.
   - Withdraw: To withdraw Ether, enter the amount (in wei) in the withdraw field, and click withdraw.
   - Get Balance: To check your balance, click the getBalance button.

## Testing

1. Select a test account in Remix VM

![image](https://github.com/user-attachments/assets/23d61f3a-8c57-49da-89aa-32b5277874ff)

2. Select the amount you want to deposit

![image](https://github.com/user-attachments/assets/026016d1-0e44-4f4e-b9c8-5e65e67d53df)

3. Hit Deposit to deposit the amount

![image](https://github.com/user-attachments/assets/e7aabffd-9408-41b1-ae08-7ca49c085f26)

4. Hit Get Balance to view the current balance

![image](https://github.com/user-attachments/assets/f3fdef58-ae43-4253-903d-b940aac2ce76)