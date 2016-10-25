# propositional-logic-inference

A propositional-logic-inference engine. support model-checking, resolution, forward-chaining algorithm.

# How to

1. use git clone to download the repository.
2. `cd propositional-logic-inference`
3. `make` will generate a `myyacc` executable.
4. `./myyacc` will generate a `dist` directory. 
5. `cd dist`
5. `make` will generate a `dcompile` executable.
6. `./dcompile -code ./data/logic.code` execute the default file `./dist/data/logic.code`


# Sample Code:

```
symbols: A, B, L, M, P, Q, R1, R2, R3, R4, R5, R6;

relations:
	R1 := P => Q;
	R2 := L & M => P;
	R3 := B & L => M;
	R4 := A & P => L;
	R5 := A & B => L;
	R6 := A & B;

KB: R1 & R2 & R3 & R4 & R5 & R6;

alpha: Q;
```

a DSL(domain specific language) contains 4 parts:

1. symbols -- all the symbol you have used should appear in the `symbols` part.
2. relations -- define abbr of Sentence, just make KB or alpha easy to describe.
3. KB -- define truth of the knowledge base.
4. alpha -- the Sentence need to be query.


