# Lab1

​	建议使用docker compose搭建

​	这个实验直接找fabric官网的test-network搭建即可



# lab2

​	geth得下1.11.6版本

初始化创世块

```bash
geth --datadir data0 init genesis.json
```

启动

```bash
geth --http --nodiscover --datadir  "./data0"  --port 30303 --http.api db,eth,net,web3 --http.corsdomain "*" --networkid 1001 --ipcdisable --allow-insecure-unlock console --rpc.enabledeprecatedpersonal
```

解锁账户

```bash
personal.unlockAccount(eth.accounts[0])
personal.unlockAccount(eth.accounts[1])
```

挖矿

```bash
miner.setEtherbase(eth.accounts[2])
miner.start()
```

