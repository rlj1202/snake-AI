# snake-AI
## 아주대학교 학술제 콘테스트

1. `python3`, `gcc`가 깔려있고 환경변수 설정이 완료된 상태여야함
2. `python3` 필요 패키지로는 `pygame`, `numpy` 가 필요하며,

```batch
pip3 install pygame numpy
```

 위 커멘드 한 줄로 설치 가능. 가상환경 구성은 본인 재량.

MinGW 설치 : https://hoy.kr/mFNBL

- `python3 main.py --play` : 게임을 직접 플레이 해볼 수 있음
- `python3 main.py` : 1000번 시행 후 평균 score을 계산, 출력
- `python3 main.py --visual` : 유저가 짠 함수의 결과를 눈으로 확인할 수 있음

위 커맨드를 입력했는데 반응이 없을 때: `python3` -> `python` 으로 바꿔서 입력

### 옵션
-	`-board_size x` : 보드의 크기가 `x`칸이 됨. 기본값은 `10`
-	`-time x` : 한판의 길이가 `x`로 제한됨. 기본값은 `500`
