#include <stdio.h>
#include <ctype.h>

#define PRODUCT_MAX_SIZE 32
#define USER_MAX_SIZE 32
#define ORDER_MAX_SIZE 512

const char* MENU_G_FILE_NAME = "우수 구매자 정보.txt";
const char* MENU_H_FILE_NAME = "당일 구매자 명단.txt";

struct Product
{
	char code;					// 상품 코드
	char* name;					// 상품 이름
	int price;					// 상품 가격
	int count;					// 상품 재고
};

struct User
{
	int id;						// 회원 번호
	char* name;					// 회원 이름
	int point;					// 보유 포인트
	int total;					// 총 구매액
};

struct Order
{
	int user_id;				// 회원 번호
	char code;					// 상품 코드
	int count;					// 구매 수량
};

void init();

void menu_user();
void menu_user_buy(struct User* user);

void menu_admin();
void menu_admin_a();
void menu_admin_b();
void menu_admin_c();
void menu_admin_d();
void menu_admin_e();
void menu_admin_f();
void menu_admin_g();
void menu_admin_h();

struct User* get_user(int id);
struct Product* get_product(char code);
int priceToPoint(int price);

struct Product products[PRODUCT_MAX_SIZE] = {
	{ 'A', "Apple", 12000, 50 },
	{ 'B', "Bread", 8000, 30 },
	{ 'C', "Coffee", 15000, 80 },
	{ 'D', "Desk", 100000, 20 },
	{ 'E', "Euiod", 56000, 70 }
};

struct User users[USER_MAX_SIZE] = {
	{ 101, "Kim", 100, 0 },
	{ 102, "Lee", 90, 0 },
	{ 103, "Park", 120, 0 },
	{ 105, "Chang", 50, 0 }
};

struct Order orders[ORDER_MAX_SIZE];
int order_count = 0;

int main() {
	while (1) {
		init();
	}

	return 0;
}

void init() {
	printf("-------------------------------------------\n");
	printf("1. 회원 메뉴 이동\n");
	printf("2. 관리자 메뉴 이동\n");
	printf("\n");
	printf("x. 프로그램 종료\n");
	printf("메뉴 입력 > ");

	char input;
	scanf(" %c", &input);
	system("cls");
	if (isalpha(input)) {
		input = tolower(input);
	}
	switch (input)
	{
	case '1':
		menu_user();
		break;
	case '2':
		menu_admin();
		break;
	case 'x':
		printf("프로그램을 종료합니다.\n");
		exit(0);
		break;
	default:
		break;
	}

	system("pause");
	system("cls");
}

struct User* get_user(int id) {
	for (int i = 0; i < USER_MAX_SIZE; i++) {
		if (users[i].id == id) {
			return &users[i];
		}
	}

	return NULL;
}

struct Product* get_product(char code) {
	for (int i = 0; i < PRODUCT_MAX_SIZE; i++) {
		if (products[i].code == code) {
			return &products[i];
		}
	}

	return NULL;
}

int priceToPoint(int price) {
	if (price < 10000) {
		return (int)(0.01 * price);
	}
	else if (price < 50000) {
		return (int)(0.03 * price);
	}
	else if (price < 100000) {
		return (int)(0.05 * price);
	}
	else {
		return (int)(0.07 * price);
	}
}

void menu_user() {
	int id;
	struct User* user;

	printf("회원 번호를 입력하세요 : ");
	scanf("%d", &id);

	while ((user = get_user(id)) == 0) {
		printf("Error: 회원 번호가 존재하지 않습니다. 다시 입력하세요 : ");
		scanf("%d", &id);
	}

	menu_user_buy(user);
}

void menu_user_buy(struct User* user) {
	system("cls");
	printf("%s님 안녕하세요.\n", user->name);
	printf("* 종료를 원하시면 X를 입력하세요.\n");
	while (1)
	{
		struct Product* product;
		printf("구매 할 상품 코드를 입력하세요 > ");

		char code;
		scanf(" %c", &code);
		code = toupper(code);
		if (code == 'X') {
			break;
		}

		product = get_product(code);
		if (product == NULL || product->name == NULL) {
			printf("Error: 상품 코드가 존재하지 않습니다.\n");
			continue;
		}

		printf("구매 할 상품의 수량을 입력하세요 > ");

		int count;
		scanf("%d", &count);

		if (count > product->count) {
			printf("Error: 상품의 재고가 부족합니다.\n");
			continue;
		}

		int price = product->price * count;
		user->total += price;
		user->point += priceToPoint(price);
		product->count -= count;

		orders[order_count++] = (struct Order){ // 주문 내역 저장
			user->id,
			product->code,
			count
		};

		printf("상품을 성공적으로 구매했습니다.\n");
		printf("현재 %s님의 총 구매액은 %d원이며, 보유 포인트는 %d점입니다.\n", user->name, user->total, user->point);
		system("pause");
		system("cls");
	}
}

void menu_admin() {
	while (1)
	{
		printf("-------------------------------------------\n");
		printf("a. 전체 회원 정보 출력\n");
		printf("b. 보유 포인트 평균 출력\n");
		printf("c. 당일 판매액 평균 출력\n");
		printf("d. 최대 금액 구입자 조회\n");
		printf("e. 최대 판매액 조회\n");
		printf("f. 구매자 개별 정보 조회\n");
		printf("g. 우수 구매자 정보 파일 저장\n");
		printf("h. 당일 구매자 명단 파일 저장\n");
		printf("\n");
		printf("x. 메인 메뉴 이동\n");
		printf("메뉴 입력 > ");

		char input;
		scanf(" %c", &input);
		system("cls");
		if (isalpha(input)) {
			input = tolower(input);
		}
		switch (input)
		{
		case 'a':
			menu_admin_a();
			break;
		case 'b':
			menu_admin_b();
			break;
		case 'c':
			menu_admin_c();
			break;
		case 'd':
			menu_admin_d();
			break;
		case 'e':
			menu_admin_e();
			break;
		case 'f':
			menu_admin_f();
			break;
		case 'g':
			menu_admin_g();
			break;
		case 'h':
			menu_admin_h();
			break;
		case 'x':
			printf("메인 메뉴로 이동합니다.\n");
			return;
		default:
			break;
		}

		system("pause");
		system("cls");
	}
}

void swapUsers(struct User* a, struct User* b) {
	struct User temp = *a;
	*a = *b;
	*b = temp;
}

void sortByTotal(struct User* users, int size) {
	for (int i = 0; i < size - 1; i++) {
		int max_index = i;
		for (int j = i + 1; j < size; j++) {
			if (users[j].total > users[max_index].total) {
				max_index = j;
			}
		}

		swapUsers(&users[i], &users[max_index]);
	}
}

void menu_admin_a() {
	printf("전체 회원 정보를 출력합니다.\n");
	printf("회원 번호\t회원 이름\t보유 포인트\t총 구매액\n");

	sortByTotal(users, USER_MAX_SIZE);
	for (int i = 0; i < USER_MAX_SIZE; i++) {
		struct User* user = &users[i];
		if (user->name == NULL) {
			continue;
		}

		printf("%d\t%s\t%d\t%d\n", user->id, user->name, user->point, user->total);
	}
}

void menu_admin_b() {
	printf("보유 포인트 평균을 출력합니다.\n");
	int sum = 0;
	int count = 0;
	for (int i = 0; i < USER_MAX_SIZE; i++) {
		struct User* user = &users[i];
		if (user->name == NULL) {
			continue;
		}

		sum += user->point;
		count++;
	}

	printf("보유 포인트 평균은 %d점입니다.\n", sum / count);
}

void menu_admin_c() {
	printf("당일 판매액 평균을 출력합니다.\n");
	int sum = 0;
	int count = 0;
	for (int i = 0; i < order_count; i++) {
		struct Order* order = &orders[i];
		struct Product* product = get_product(order->code);
		if (product == NULL || product->name == NULL) {
			continue;
		}

		sum += product->price * order->count;
		count++;
	}

	printf("당일 판매액 평균은 %d원입니다.\n", sum / count);
}

void menu_admin_d() {
	printf("최대 금액 구입자를 조회합니다.\n");
	int max = 0;
	struct User* max_user = NULL;
	for (int i = 0; i < USER_MAX_SIZE; i++) {
		struct User* user = &users[i];
		if (user->name == NULL) {
			continue;
		}

		if (user->total > max) {
			max = user->total;
			max_user = user;
		}
	}

	printf("최대 금액 구입자는 %s님입니다.\n", max_user->name);
	printf("총 구매액은 %d원입니다.\n", max_user->total);
}

void menu_admin_e() {
	printf("최대 판매액을 조회합니다.\n");

	int max = 0;
	for (int i = 0; i < order_count; i++) {
		struct Order* order = &orders[i];
		struct Product* product = get_product(order->code);
		if (product == NULL || product->name == NULL) {
			continue;
		}

		int price = product->price * order->count;
		if (price > max) {
			max = price;
		}
	}

	printf("최대 판매액은 %d원입니다.\n", max);
}

void menu_admin_f() {
	printf("구매자 개별 정보를 조회합니다.\n");
	printf("회원 번호를 입력하세요 : ");

	int id;
	scanf("%d", &id);

	struct User* user = get_user(id);
	if (user == NULL) {
		printf("Error: 회원 번호가 존재하지 않습니다.\n");
		return;
	}

	printf("회원 번호\t회원 이름\t보유 포인트\t총 구매액\n");
	printf("%d\t%s\t%d\t%d\n", user->id, user->name, user->point, user->total);
}

void menu_admin_g() {
	printf("우수 구매자 정보를 파일로 저장합니다.\n");
	FILE* file = fopen(MENU_G_FILE_NAME, "w");
	if (file == NULL) {
		printf("Error: 파일을 열 수 없습니다.\n");
		return;
	}

	fprintf(file, "회원 번호\t회원 이름\t보유 포인트\t총 구매액\n");
	for (int i = 0; i < USER_MAX_SIZE; i++) {
		struct User* user = &users[i];
		if (user->name == NULL) {
			continue;
		}

		if (user->total < 10000) {
			continue;
		}
		fprintf(file, "%d\t%s\t%d\t%d\n", user->id, user->name, user->point, user->total);
	}

	fclose(file);
}

void menu_admin_h() {
	printf("당일 구매자 명단을 파일로 저장합니다.\n");
	FILE* file = fopen(MENU_H_FILE_NAME, "w");
	if (file == NULL) {
		printf("Error: 파일을 열 수 없습니다.\n");
		return;
	}

	fprintf(file, "회원 번호\t상품 코드\t구매 수량\n");
	for (int i = 0; i < order_count; i++) {
		struct Order* order = &orders[i];
		struct Product* product = get_product(order->code);
		if (product == NULL || product->name == NULL) {
			continue;
		}

		fprintf(file, "%d\t%c\t%d\n", order->user_id, product->code, order->count);
	}

	fclose(file);
}