# cordle

![demo](/img/demo.png)

Wordle game in C.

## TODO
- fix misreading duplicate letters as out of position
- proper checking of input length
	 - `fgets` reads from `stdin` without overflow, but doesn't warn of additional characters entered
