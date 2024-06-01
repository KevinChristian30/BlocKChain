# BlocKChain
> A simplified blockchain simulator

This project implements a 'backed' linked list data structure to do operations that is stored on a text file. It simulates a ledger that stores a list of transactions. It is inspired by Bitcoin's whitepaper, it's simplified to fit certain requirements.

This monorepo consists of two projects, one is for the miners, and the other is for the client.

## Installing / Getting started

```shell
git clone https://github.com/KevinChristian30/BlocKChain
```

The command above will fetch the repository.

### Initial Configuration

```shell
cd client
make
```

The command above will go to the client folder and compile the client application.

```shell
cd ../miner
make
```

The command above will go to the miner folder and compile the miner application.

## Features
* Authentication that is both used by the miner and client application.
* Clients can send and receive money.
* Search client by name.
* Pagination using a Circular Doubly Linked List.
* Miners can mine to finalize the transaction.
