# dena-review
Connect four in C

## 四目並べ

2人のプレイヤーが交互にコマを下から積み重ねて、先に縦・横・斜めいずれかに直線状に4つ並べた方が勝ちになる。平面方向には任意の場所を選ぶことができるが、垂直方向に対しては重力の関係で先に入っているコマの真上（または盤面のすぐ上）にしかコマを置けないという点がこのゲームのキーポイントになっている。

https://github.com/hrm5yu/dena-review/blob/main/gif/

## 操作方法

	右に移動 D
	左に移動 A
	玉を置く space

## ゲームの始め方

```
$ git clone https://github.com/hrm5yu/dena-review.git
$ cd dena-review
$ ./connect_four