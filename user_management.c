#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct {
    char username[30];
    char password[30];
} User;

User users[MAX_USERS];
int user_count = 0;

void register_user();
int user_login();
void fix_fgets_input(char*);
void input_password(char*);

int main() {
    int option;
    while (1) {
        printf("\nДобро пожаловать в банковский менеджмент");
        printf("\n1) Регистрация");
        printf("\n2) Войти");
        printf("\n3) Выйти");
        printf("\nВыбрать: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                register_user();
                break;
            case 2: {
                int user_index = user_login();
                if (user_index >= 0) {
                    printf("\nУспех! Ваш логин: %s\n", users[user_index].username);
                } else {
                    printf("\nОшибка входа\n");
                }
                break;
            }
            case 3:
                printf("\nВы вышли из программы\n");
                return 0;
            default:
                printf("\nНеправильный ввод. Пожалуйста, введите правильный вариант\n");
                break;
        }
    }
    return 0;
}

void register_user() {
    if (user_count == MAX_USERS) {
        printf("\nМаксимум %d пользователей\n", MAX_USERS);
        return;
    }
    int new_index = user_count;
    printf("\nВведите имя пользователя: ");
    fgets(users[new_index].username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(users[new_index].username);
    input_password(users[new_index].password);
    user_count++;
    printf("\nРегистрация прошла успешно!\n");
}

int user_login() {
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    printf("\nВведите имя пользователя: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);
    input_password(password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return i;
        }
    }
    return -1;
}

void input_password(char* password) {
    printf("\nВведите пароль: ");
    fgets(password, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(password);
}

void fix_fgets_input(char* string) {
    int index = strcspn(string, "\n");
    if (index < strlen(string)) {
        string[index] = '\0';
    }
}
