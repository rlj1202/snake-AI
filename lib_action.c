#include <string.h>
#include <math.h>
#include <stdio.h>

// board : 10 * 10 char array : 각 행의 메모리가 연속적이진 않음
// board_size = 10
// 보드 위에서
// snake의 머리 = 3
// snake의 몸통 = 2
// food = 1

// 유저는 뱀의 다음 행동을 결정하는 [0, 3] 네 숫자 중 하나를 반환해야 함.
// 0 : left
// 1 : right
// 2 : up
// 3 : down
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

// body : length * 2 char array
//  body[0] : 머리, body[1 ~ len - 1] : 몸통
//  body[i][0] : y값, board[i][1] : x값

// head : 보고있는 방향
// remain_time : 게임 종료까지 남은 턴. 0이 되면 종료

int dx[] = {-1, 1, 0, 0};
int dy[] = { 0, 0, -1, 1};

// LEFT, RIGHT, UP, DOWN
int turn_left[] = {DOWN, UP, LEFT, RIGHT};
int turn_right[] = {UP, DOWN, RIGHT, LEFT};

typedef struct vec2 {
	union {
		struct { int r, c; };
		struct { int y, x; };
	};
} vec2;

vec2 sub(vec2 a, vec2 b) {
	vec2 result = {a.r - b.r, a.c - b.c};
	return result;
}

vec2 add(vec2 a, vec2 b) {
	vec2 result = {a.r + b.r, a.c + b.c};
	return result;
}

int dot(vec2 a, vec2 b) {
	int result = a.x * b.x + a.y * b.y;
	return result;
}

int cross(vec2 a, vec2 b) {
	int result = a.x * b.y - a.y * b.x;
	return result;
}

int equals(vec2 a, vec2 b) {
	return (a.r == b.r) && (a.c == b.c);
}

int is_out_of_bound(vec2 v) {
	return v.x < 0 || v.y < 0 || v.x >= 10 || v.y >= 10;
}

int does_collide(vec2 v, const char **body, int length) {
	for (int l = 0; l < length; l++) {
		vec2 b = {body[l][0], body[l][1]};
		if (equals(v, b))
			return 1;
	}
	return is_out_of_bound(v);
}

vec2 invert_y(vec2 v) {
	vec2 result = v;
	result.y *= -1;
	return result;
}

void print_vec2(vec2 v) {
	printf("(x: %d, y: %d)", v.x, v.r);
}

vec2 dir_vec(int dir) {
	vec2 result = {dy[dir], dx[dir]};
	return result;
}

char tmp[12][12];

// . . . . . .
// . . 2 3 4 .
// . . 1 . 5 .
// . . . R 6 L
// . . . . . .

int check_valid_move(vec2 v, const char **board, const char **body, int length) {
	// copy board only snake
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (board[r][c] > 1) tmp[r][c] = board[r][c];
			else tmp[r][c] = 0;
		}
	}

	for (int l = 0; l < length; l++) {
		vec2 v = {body[l][0], body[l][1]};
		tmp[v.r][v.c] = length - l;
	}

	// TODO

	return 0;
}

// 함수명과 인자의 타입 수정 금지 !
int action_decision(const char **board, const char **body, int length, int head, int remain_time) {
	vec2 head_point = {body[0][0], body[0][1]};
	vec2 head_dir = {dy[head], dx[head]};
	vec2 food_point = {-1, -1};

	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (board[r][c] == 1) {
				food_point.r = r;
				food_point.c = c;
			}
		}
	}

	vec2 food_dir = sub(food_point, head_point);

	//

	int c = cross(
			invert_y(head_dir),
			invert_y(food_dir)
			);
	int d = dot(
			invert_y(head_dir),
			invert_y(food_dir)
			);

	int left = 0;
	int right = 0;

	if (d == 0) {
		if (c > 0) {
			left = 1;
		} else if (c < 0) {
			right = 1;
		}
	} else if (d > 0) {

	} else {
		//left = 1;
		//right = 1;
	}

	printf("left = %d, right = %d\n", left, right);

	int next_dir = head;

	if (left && !does_collide(
				add(head_point, dir_vec(turn_left[head])),
				body, length)) {
		printf("left\n");
		next_dir = turn_left[head];
	} else if (right && !does_collide(
				add(head_point, dir_vec(turn_right[head])),
				body, length)) {
		printf("right\n");
		next_dir = turn_right[head];
	} else {
		printf("straight\n");

		vec2 next_point = add(head_point, dir_vec(head));
		if (does_collide(next_point, body, length)) {
			if (!does_collide(
						add(head_point, dir_vec(turn_left[head])),
						body, length)) {
				printf("left\n");
				next_dir = turn_left[head];
			} else if (!does_collide(
						add(head_point, dir_vec(turn_right[head])),
						body, length)) {
				printf("right\n");
				next_dir = turn_right[head];
			}
		}
	}

	vec2 v_left = add(head_point, dir_vec(turn_left[head]));
	vec2 v_right = add(head_point, dir_vec(turn_right[head]));
	printf("cross = %d, dot = %d\n", c, d);
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			vec2 v = {r, c};
			if (equals(v, v_left)) {
				printf("%c ", 'L');
			} else if (equals(v, v_right)) {
				printf("%c ", 'R');
			} else {
				printf("%d ", board[r][c]);
			}
		}
		printf("\n");
	}
	printf("################################################################################\n");

	return next_dir;
}
