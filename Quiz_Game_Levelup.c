#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Question {
    char question[100];
    char options[4][50];
    int correctOption;
    int difficultyLevel;
};

void bubbleSort(struct Question questions[], int numQuestions) {
    for (int i = 0; i < numQuestions - 1; i++) {
        for (int j = 0; j < numQuestions - i - 1; j++) {
            if (questions[j].difficultyLevel > questions[j + 1].difficultyLevel) {
                struct Question temp = questions[j];
                questions[j] = questions[j + 1];
                questions[j + 1] = temp;
            }
        }
    }
}

void displayQuestion(struct Question q) {
    printf("%s\n", q.question);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, q.options[i]);
    }
}

int playQuizLevel(struct Question questions[], int numQuestions, int level) {
    int score = 0;

    for (int i = 0; i < numQuestions; i++) {
        if (questions[i].difficultyLevel != level) {
            continue;
        }

        printf("\nQuestion %d (Difficulty Level %d):\n", i + 1, questions[i].difficultyLevel);
        displayQuestion(questions[i]);

        int userAnswer;
        printf("Your answer (1-4): ");
        scanf("%d", &userAnswer);

        if (userAnswer == questions[i].correctOption) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is %d. %s\n", questions[i].correctOption,
                   questions[i].options[questions[i].correctOption - 1]);
        }
    }

    return score;
}

int main() {
    struct Question questions[] = {
        {"What is the capital of France?", {"Paris", "London", "Berlin", "Madrid"}, 1, 1},
        {"Which planet is known as the Red Planet?", {"Mars", "Venus", "Jupiter", "Saturn"}, 1, 1},
        {"What is the largest mammal?", {"Elephant", "Whale Shark", "Blue Whale", "Giraffe"}, 3, 1},
        {"What is the chemical symbol for gold?", {"Au", "Ag", "Fe", "Hg"}, 1, 2},
        {"Which gas do plants absorb from the atmosphere?", {"Oxygen", "Carbon Dioxide", "Nitrogen", "Hydrogen"}, 2, 2},
        {"What is the freezing point of water in Celsius?", {"0°C", "-10°C", "100°C", "25°C"}, 1, 2},
        {"What is the smallest prime number?", {"1", "2", "3", "4"}, 2, 3},
        {"Which gas makes up the majority of the Earth's atmosphere?", {"Oxygen", "Carbon Dioxide", "Nitrogen", "Hydrogen"}, 3, 3},
        {"What is the largest planet in our solar system?", {"Earth", "Mars", "Jupiter", "Venus"}, 3, 3},
    };

    int numQuestions = sizeof(questions) / sizeof(questions[0]);

    bubbleSort(questions, numQuestions);

    int totalScore = 0;
    int minCorrectAnswers = 2;
    int unlocked = 1;

    for (int level = 1; level <= 3; level++) {
        printf("\nLevel %d\n", level);
        int levelScore = playQuizLevel(questions, numQuestions, level);
        printf("Your score for Level %d: %d out of %d\n", level, levelScore, numQuestions / 3);
        totalScore += levelScore;

        if (levelScore < minCorrectAnswers) {
            unlocked = 0;
            printf("Sorry, you need at least %d correct answers to unlock the next level.\n", minCorrectAnswers);
            break;
        }

        if (level < 3 && unlocked) {
            printf("Congratulations! You have unlocked the next level.\n");
        }
    }

    printf("\nQuiz completed. Your total score: %d\n", totalScore);

    return 0;
}
