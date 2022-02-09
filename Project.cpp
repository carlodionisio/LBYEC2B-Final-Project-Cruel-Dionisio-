#include <stdio.h>
#include <ctype.h>

#define NAME_LENGTH 51
#define KG_TO_LBS_CONSTANT 2.204623

typedef struct Person {
    char name[NAME_LENGTH];
    int age;
    int is_male;
    double height;
    double weight;
} person;

enum BMI {
    UNDER_WEIGHT,
    NORMAL_WEIGHT,
    OVER_WEIGHT
};

void input_person_details(person* p) {
    printf("Input your name: ");
    fgets(p->name, NAME_LENGTH, stdin);

    printf("Input your age: ");
    scanf("%d", &p->age);

    printf("Input your gender [M/F]: ");
    char c = ' ';
    getc(stdin); // Consume input
    while (c != 'M' && c != 'F') {
        c = getc(stdin);
        c = toupper(c);
        if (c != 'M' && c != 'F') {
            printf("Input should be [M/F]: ");
        }
    }
    p->is_male = c == 'M';

    printf("Input your height(in meters): ");
    scanf("%lf", &p->height);

    printf("Input you weight(in kg): ");
    scanf("%lf", &p->weight);
}

double convert_m_to_cm(double m) {
    return m * 100.0;
}

double calculate_bmi(person* p) {
    return p->weight / p->height / p->height;
}

double calculate_ree(person* p) {
    double height = convert_m_to_cm(p->height);
    double add = -161.0;
    if (p->is_male) {
        add = 5.0;
    }
    return 10.0 * p->weight +
        6.25 * height -
        5.0 * p->age + add;
}

int classify_bmi(double bmi) {
    if (bmi < 18.5) {
        return UNDER_WEIGHT;
    } else if (bmi < 24.9) {
        return NORMAL_WEIGHT;
    }

    return OVER_WEIGHT;
}

// 0 - Maintain Weight
// 1 - Gain Weight
// 2 - Lose Weight
char todo(int classification) {
    char c = 0;
    if (classification == UNDER_WEIGHT) {
        printf("It is recommended for you to gain weight\n");
        return 1;
    } else if (classification == OVER_WEIGHT) {
        printf("It is recommended for you to lose weight\n");
        return 2;
    } else {
        getc(stdin);
        while (c != 'a' && c != 'b') {
            printf("What would you like to do?\n");
            printf("(a) Maintain Weight\n");
            printf("(b) Gain Weight\n");
            printf("> ");
            c = getc(stdin);
            c = tolower(c);
            if (c != 'a' && c != 'b') {
                printf("Invalid input, try again...\n");
            }
        }
        return (int) (c - 'a'); 
    }
}

double ask_activity() {
    char c = ' ';
    getc(stdin);
    while (c < 'a' || c > 'd') {
        printf("Describe your level of activity?\n");
        printf("(a) Sendentary\n");
        printf("(b) Light Activity\n");
        printf("(c) Moderate Activity\n");
        printf("(d) Very Active\n");
        printf("> ");
        c = getc(stdin);
        c = tolower(c);
        if (c < 'a' || c > 'd') {
            printf("Invalid input, try again...\n");
        }
    }

    if (c == 'a') {
        return 1.2;
    } if (c == 'b') {
        return 1.375;
    } if (c == 'c') {
        return 1.55;
    }
    return 1.725; 
}

// Print Functions
void print_bmi(double bmi, int classification) {
    printf("\nYour calculated BMI is %.2lf (", bmi);
    if (classification == UNDER_WEIGHT) {
        printf("Under Weight");
    } else if (classification == NORMAL_WEIGHT) {
        printf("Normal Weight");
    } else {
        printf("Over Weight");
    }
    printf(")\n\n");
}

void print_consumption(int act, double calories) {
    if (act == 0) { // Maintain
        printf("You should be consuming %.3lf calories per day\n", calories);
        printf("Protein  25-40%%\n");
        printf("Carbs    35-55%%\n");
        printf("Fat      25-45%%\n");
    } else if (act == 1) { // Gain
        printf("You should be consuming more than %.3lf calories per day\n", calories);
        printf("Protein  35%%\n");
        printf("Carbs    45%%\n");
        printf("Fat      20%%\n");
    } else { // Lose
        printf("You should be consuming less than %.3lf calories per day\n", calories);
        printf("Protein  35-50%%\n");
        printf("Carbs    25-45%%\n");
        printf("Fat      20-35%%\n");
    }
    printf("\n");
}

void print_activity(int act) {
    if (act == 0) { // Maintain
        printf("Push ups        10 reps / 3 sets\n");
        printf("Sit ups         10 reps / 3 sets\n");
        printf("Squats          10 reps / 3 sets\n");
        printf("Lunges          10 reps / 3 sets\n");
        printf("Jumping jacks   20 reps / 3 sets\n");
        printf("Jogging         1 hr\n");
    } else if (act == 1) { // Gain
        printf("Push ups        15 reps / 5 sets\n");
        printf("Pull ups        10 reps / 5 sets\n");
        printf("Squats          15 reps / 5 sets\n");
        printf("Sit ups         20 reps / 5 sets\n");
        printf("Jogging         30 mins\n");
        printf("Plank           2 mins / 5 sets\n");
    } else { // Lose
        printf("Dynamic Stretch 10 reps / each\n");
        printf("Jumping jacks   30 reps / 30 sets\n");
        printf("Stationary Jump 20 reps / 3 sets\n");
        printf("High Knees      20 reps /53 sets\n");
        printf("Jump Rope       30 mins\n");
        printf("Jogging         2 hrs\n");
    }
    printf("\n");
}

int main() {
    person p;
    input_person_details(&p);

    double bmi = calculate_bmi(&p);
    int bmi_classification = classify_bmi(bmi);
    print_bmi(bmi, bmi_classification);

    int act = todo(bmi_classification);
    double factor = ask_activity();
    double ree = calculate_ree(&p);
    double tdee = ree * factor;
    
    printf("\n");
    print_consumption(act, tdee);
    print_activity(act);

    return 0;
}
