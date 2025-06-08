// main.cpp
// C++ SFML Гра-Кросворд (українська мова, шрифт OpenSans, 3 рівні, з анімаціями навігації,
// та кнопкою "Перевірити", яка показує зелену галочку або червоний хрест на 5 секунд)

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

// Визначення клітинки для однієї літери
struct Cell {
    bool editable;            // Чи є ця клітинка частиною слота (біла) чи просто фоном?
    wchar_t letter;           // Поточна літера (введена гравцем), L'\0' якщо порожня
    wchar_t solution;         // Літера-відповідь (для перевірки)
    int number;               // Номер підказки, якщо це перша клітинка слота, інакше 0
    Cell() : editable(false), letter(L'\0'), solution(L'\0'), number(0) {}
};

// Визначення підказки (у спрощеній версії тільки горизонтальні)
struct Clue {
    int number;
    std::wstring text;
    int row, col;    // Початкова клітинка слота
    int length;
    std::wstring answer; // Слово-відповідь
};

// Рівень складається з сітки та підказок
struct Level {
    int rows, cols;
    std::vector<std::vector<Cell>> grid;
    std::vector<Clue> clues;
};

int main() {
    // Використовуємо українську локаль для підтримки широких символів
    std::locale::global(std::locale(""));

    // Налаштування вікна
    const int CELL_SIZE = 50;
    const int GRID_ROWS = 7;
    const int GRID_COLS = 7;
    const int CLUE_AREA_HEIGHT = 200;
    const int BUTTON_HEIGHT = 50;
    const int WINDOW_WIDTH = GRID_COLS * CELL_SIZE + 200; // додатковий простір для стрілок
    const int WINDOW_HEIGHT = GRID_ROWS * CELL_SIZE + CLUE_AREA_HEIGHT + BUTTON_HEIGHT + 20;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Кросворд (SFML)");

    // Завантаження шрифту OpenSans (переконайтеся, що OpenSans-Regular.ttf є в робочій директорії)
    sf::Font font;
    if (!font.loadFromFile("OpenSans-Regular.ttf")) {
        // Обробка помилки (наприклад, файл не знайдено)
        return -1;
    }

    // Підготовка трьох рівнів
    std::vector<Level> levels(3);

    // --- Рівень 1 ---
    {
        Level& lvl = levels[0];
        lvl.rows = GRID_ROWS;
        lvl.cols = GRID_COLS;
        lvl.grid.assign(lvl.rows, std::vector<Cell>(lvl.cols));

        // Визначення 3 горизонтальних слотів:
        // 1 По горизонталі: ряд=1, колонка=1, довжина=5, відповідь="КНИГА"
        lvl.clues.push_back({1, L"Що читають?", 1, 1, 5, L"КНИГА"});
        // 2 По горизонталі: ряд=3, колонка=1, довжина=4, відповідь="МОВА"
        lvl.clues.push_back({2, L"Який засіб спілкування?", 3, 1, 4, L"МОВА"});
        // 3 По горизонталі: ряд=5, колонка=1, довжина=5, відповідь="ВЕСНА"
        lvl.clues.push_back({3, L"Пора року після зими?", 5, 1, 5, L"ВЕСНА"});

        // Позначення клітинок як редагованих та присвоєння відповіді та номера
        for (auto& clue : lvl.clues) {
            int r = clue.row, c = clue.col;
            for (int i = 0; i < clue.length; ++i) {
                Cell& cell = lvl.grid[r][c + i];
                cell.editable = true;
                cell.solution = clue.answer[i];
                if (i == 0) {
                    cell.number = clue.number;
                }
            }
        }
    }

    // --- Рівень 2 ---
    {
        Level& lvl = levels[1];
        lvl.rows = GRID_ROWS;
        lvl.cols = GRID_COLS;
        lvl.grid.assign(lvl.rows, std::vector<Cell>(lvl.cols));

        // Визначення 3 горизонтальних слотів:
        // 1 По горизонталі: ряд=1, колонка=1, довжина=5, відповідь="СОНЦЕ"
        lvl.clues.push_back({1, L"Що світить удень?", 1, 1, 5, L"СОНЦЕ"});
        // 2 По горизонталі: ряд=3, колонка=1, довжина=4, відповідь="ВОДА"
        lvl.clues.push_back({2, L"Без чого не може жити організм?", 3, 1, 4, L"ВОДА"});
        // 3 По горизонталі: ряд=5, колонка=1, довжина=5, відповідь="ЗЕМЛЯ"
        lvl.clues.push_back({3, L"Планета, де ми живемо?", 5, 1, 5, L"ЗЕМЛЯ"});

        // Позначення клітинок як редагованих та присвоєння відповіді та номера
        for (auto& clue : lvl.clues) {
            int r = clue.row, c = clue.col;
            for (int i = 0; i < clue.length; ++i) {
                Cell& cell = lvl.grid[r][c + i];
                cell.editable = true;
                cell.solution = clue.answer[i];
                if (i == 0) {
                    cell.number = clue.number;
                }
            }
        }
    }

    // --- Рівень 3 ---
    {
        Level& lvl = levels[2];
        lvl.rows = GRID_ROWS;
        lvl.cols = GRID_COLS;
        lvl.grid.assign(lvl.rows, std::vector<Cell>(lvl.cols));

        // Визначення 3 горизонтальних слотів:
        // 1 По горизонталі: ряд=1, колонка=1, довжина=5, відповідь="РАДІО"
        lvl.clues.push_back({1, L"Що передає звукові хвилі?", 1, 1, 5, L"РАДІО"});
        // 2 По горизонталі: ряд=3, колонка=1, довжина=4, відповідь="КІНО"
        lvl.clues.push_back({2, L"Як коротко називають кінотеатр?", 3, 1, 4, L"КІНО"});
        // 3 По горизонталі: ряд=5, колонка=1, довжина=5, відповідь="МУЗЕЙ"
        lvl.clues.push_back({3, L"Заклад для збереження історії?", 5, 1, 5, L"МУЗЕЙ"});

        // Позначення клітинок як редагованих та присвоєння відповіді та номера
        for (auto& clue : lvl.clues) {
            int r = clue.row, c = clue.col;
            for (int i = 0; i < clue.length; ++i) {
                Cell& cell = lvl.grid[r][c + i];
                cell.editable = true;
                cell.solution = clue.answer[i];
                if (i == 0) {
                    cell.number = clue.number;
                }
            }
        }
    }

    // Змінні стану
    int currentLevel = 0;
    bool animating = false;
    float animationOffset = 0.f; // поточний зсув по X для анімації
    float animationTarget = 0.f;
    sf::Clock animationClock;
    const float ANIMATION_DURATION = 0.5f; // секунди

    // Відстеження вибраної клітинки
    int selRow = -1, selCol = -1;

    // Змінні для перевірки результату
    bool showResult = false;
    bool resultCorrect = false;
    sf::Clock resultClock;
    const float RESULT_DURATION = 5.f; // секунди

    // Визначення кнопки "Перевірити"
    sf::RectangleShape checkButton(sf::Vector2f(200, BUTTON_HEIGHT));
    checkButton.setFillColor(sf::Color(100, 200, 100));
    checkButton.setOutlineColor(sf::Color::Black);
    checkButton.setOutlineThickness(2.f);
    // Позиція кнопки по центру під областю підказок
    float buttonX = WINDOW_WIDTH / 2.f - 100;
    float buttonY = GRID_ROWS * CELL_SIZE + CLUE_AREA_HEIGHT + 10;
    checkButton.setPosition(buttonX, buttonY);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString(L"Перевірити");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::Black);
    // Центрування тексту в кнопці
    {
        sf::FloatRect tb = buttonText.getLocalBounds();
        buttonText.setPosition(
            buttonX + (200.f - tb.width) / 2.f,
            buttonY + (BUTTON_HEIGHT / 2.f - tb.height) / 2.f - tb.top
        );
    }

    // Допоміжна функція для початку анімації до нового рівня (напрямок: +1 вправо, -1 вліво)
    auto startAnimation = [&](int direction) {
        if (animating || showResult) return;
        int newLevel = currentLevel + direction;
        if (newLevel < 0 || newLevel >= static_cast<int>(levels.size())) return;
        animating = true;
        animationClock.restart();
        animationOffset = 0.f;
        animationTarget = (direction > 0 ? -static_cast<float>(WINDOW_WIDTH) : static_cast<float>(WINDOW_WIDTH));
        currentLevel = newLevel;
        selRow = selCol = -1;
    };

    // Головний цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Закриття вікна
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Клік мишею для вибору клітинки, натискання стрілок або кнопки "Перевірити"
            if (event.type == sf::Event::MouseButtonPressed) {
                int mx = event.mouseButton.x;
                int my = event.mouseButton.y;

                // Якщо показуємо результат, ігноруємо кліки до закінчення часу
                if (showResult) {
                    continue;
                }

                // Перевірка області кліку лівої/правої стрілки (тільки якщо не анімуємо і не показуємо результат)
                if (!animating) {
                    sf::FloatRect leftArrowArea(0, WINDOW_HEIGHT / 2.f - 25, 50, 50);
                    sf::FloatRect rightArrowArea(WINDOW_WIDTH - 50, WINDOW_HEIGHT / 2.f - 25, 50, 50);
                    if (leftArrowArea.contains(mx, my)) {
                        startAnimation(-1);
                        continue;
                    } else if (rightArrowArea.contains(mx, my)) {
                        startAnimation(+1);
                        continue;
                    }
                }

                // Перевірка натискання кнопки "Перевірити"
                if (!animating && !showResult) {
                    if (checkButton.getGlobalBounds().contains(mx, my)) {
                        // Оцінка правильності поточного рівня
                        bool allCorrect = true;
                        for (int r = 0; r < GRID_ROWS; ++r) {
                            for (int c = 0; c < GRID_COLS; ++c) {
                                const Cell& cell = levels[currentLevel].grid[r][c];
                                if (cell.editable) {
                                    if (cell.letter == L'\0') {
                                        allCorrect = false;
                                        break;
                                    }
                                    if (cell.letter != cell.solution) {
                                        allCorrect = false;
                                        break;
                                    }
                                }
                            }
                            if (!allCorrect) break;
                        }
                        resultCorrect = allCorrect;
                        showResult = true;
                        resultClock.restart();
                        continue;
                    }
                }

                // Перевірка, чи клікнули всередині будь-якої редагованої клітинки поточного рівня
                if (!animating && !showResult) {
                    int gridX = mx - (WINDOW_WIDTH / 2 - GRID_COLS * CELL_SIZE / 2);
                    int gridY = my;
                    if (gridX >= 0 && gridX < GRID_COLS * CELL_SIZE && gridY >= 0 && gridY < GRID_ROWS * CELL_SIZE) {
                        int r = gridY / CELL_SIZE;
                        int c = gridX / CELL_SIZE;
                        if (r >= 0 && r < GRID_ROWS && c >= 0 && c < GRID_COLS) {
                            if (levels[currentLevel].grid[r][c].editable) {
                                selRow = r;
                                selCol = c;
                            } else {
                                selRow = selCol = -1;
                            }
                        }
                    }
                }
            }

            // Введення тексту для літер (тільки якщо не анімуємо і не показуємо результат)
            if (!animating && !showResult && event.type == sf::Event::TextEntered) {
                if (selRow >= 0 && selCol >= 0) {
                    wchar_t uni = static_cast<wchar_t>(event.text.unicode);
                    // Приймаємо тільки українські літери (А-Я, а-я, ҐҐ, Єє, Іі, Її)
                    if ((uni >= L'А' && uni <= L'я') ||
                        uni == L'ґ' || uni == L'Ґ' || uni == L'Є' || uni == L'є' ||
                        uni == L'І' || uni == L'і' || uni == L'Ї' || uni == L'ї') {
                        uni = std::towupper(uni);
                        levels[currentLevel].grid[selRow][selCol].letter = uni;
                        // Переміщення вибору до наступної клітинки в тому ж слоті, якщо вона існує
                        for (auto& clue : levels[currentLevel].clues) {
                            if (clue.row == selRow && selCol >= clue.col && selCol < clue.col + clue.length) {
                                int nextCol = selCol + 1;
                                if (nextCol < clue.col + clue.length) {
                                    selCol = nextCol;
                                }
                                break;
                            }
                        }
                    }
                    // Backspace: очищення літери
                    if (event.text.unicode == 8) {
                        levels[currentLevel].grid[selRow][selCol].letter = L'\0';
                    }
                }
            }
        }

        // Обробка анімації перемикання рівнів
        if (animating) {
            float elapsed = animationClock.getElapsedTime().asSeconds();
            float t = elapsed / ANIMATION_DURATION;
            if (t >= 1.f) {
                animating = false;
                animationOffset = 0.f;
                selRow = selCol = -1;
            } else {
                animationOffset = animationTarget * t;
            }
        }

        // Обробка часу показу результату
        if (showResult) {
            float elapsedRes = resultClock.getElapsedTime().asSeconds();
            if (elapsedRes >= RESULT_DURATION) {
                showResult = false;
            }
        }

        // Очищення вікна
        window.clear(sf::Color(250, 250, 250));

        // -------------------------------------------------
        // Малювання поточного (і під час анімації, сусіднього) рівнів
        // -------------------------------------------------
        for (int i = -1; i <= 1; ++i) {
            int lvlIdx = currentLevel + i;
            if (lvlIdx < 0 || lvlIdx >= static_cast<int>(levels.size()))
                continue;

            // Якщо не анімуємо, малюємо тільки i == 0
            if (!animating && i != 0)
                continue;

            float baseOffsetX = 0.f;
            if (animating) {
                if (i == 0) {
                    baseOffsetX = animationOffset;
                }
                else if (i == -1 && animationTarget > 0) {
                    baseOffsetX = animationOffset - WINDOW_WIDTH;
                }
                else if (i == 1 && animationTarget < 0) {
                    baseOffsetX = animationOffset + WINDOW_WIDTH;
                }
                else if (i != 0) {
                    continue;
                }
            }
            // якщо !animating, baseOffsetX = 0

            // Малювання клітинок сітки
            for (int r = 0; r < GRID_ROWS; ++r) {
                for (int c = 0; c < GRID_COLS; ++c) {
                    const Cell& cell = levels[lvlIdx].grid[r][c];
                    float x = (WINDOW_WIDTH / 2.f - (GRID_COLS * CELL_SIZE) / 2.f) + c * CELL_SIZE + baseOffsetX;
                    float y = r * CELL_SIZE;

                    // Фон клітинки
                    sf::RectangleShape rect(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                    rect.setPosition(x + 1, y + 1);
                    if (cell.editable) {
                        rect.setFillColor(sf::Color::White);
                        rect.setOutlineColor(sf::Color::Black);
                        rect.setOutlineThickness(1.f);
                    } else {
                        rect.setFillColor(sf::Color(200, 200, 200));
                        rect.setOutlineColor(sf::Color::Black);
                        rect.setOutlineThickness(1.f);
                    }
                    window.draw(rect);

                    // Номер підказки
                    if (cell.number > 0) {
                        sf::Text numText;
                        numText.setFont(font);
                        numText.setString(std::to_wstring(cell.number));
                        numText.setCharacterSize(14);
                        numText.setFillColor(sf::Color::Black);
                        numText.setPosition(x + 3, y + 2);
                        window.draw(numText);
                    }

                    // Літера, введена гравцем
                    if (cell.letter != L'\0') {
                        sf::Text letterText;
                        letterText.setFont(font);
                        std::wstring s;
                        s += cell.letter;
                        letterText.setString(s);
                        letterText.setCharacterSize(32);
                        letterText.setFillColor(sf::Color::Black);
                        // Центрування літери
                        float tx = x + CELL_SIZE / 2.f - letterText.getLocalBounds().width / 2.f;
                        float ty = y + CELL_SIZE / 2.f - letterText.getLocalBounds().height;
                        letterText.setPosition(tx, ty);
                        window.draw(letterText);
                    }
                }
            }

            // Малювання області підказок для цього рівня
            float cluesX = (WINDOW_WIDTH / 2.f - (GRID_COLS * CELL_SIZE) / 2.f) + baseOffsetX;
            float cluesY = GRID_ROWS * CELL_SIZE + 10;

            // Заголовок рівня
            sf::Text title;
            title.setFont(font);
            title.setString(L"Рівень " + std::to_wstring(lvlIdx + 1));
            title.setCharacterSize(24);
            title.setFillColor(sf::Color::Black);
            title.setPosition(cluesX, cluesY);
            window.draw(title);

            // Список підказок з достатнім інтервалом
            for (size_t iClue = 0; iClue < levels[lvlIdx].clues.size(); ++iClue) {
                const Clue& clue = levels[lvlIdx].clues[iClue];
                sf::Text clueText;
                clueText.setFont(font);
                clueText.setCharacterSize(20);
                clueText.setFillColor(sf::Color::Black);
                clueText.setPosition(cluesX, cluesY + 30 + static_cast<int>(iClue) * 40);
                std::wstring s = std::to_wstring(clue.number) + L". " + clue.text;
                clueText.setString(s);
                window.draw(clueText);
            }
        }

        // Малювання кнопки "Перевірити" (тільки якщо не анімуємо і не показуємо результат)
        if (!animating && !showResult) {
            window.draw(checkButton);
            window.draw(buttonText);
        }

        // Малювання навігаційних стрілок
        // Ліва стрілка
        {
            sf::ConvexShape arrow;
            arrow.setPointCount(3);
            arrow.setPoint(0, sf::Vector2f(40, 0));
            arrow.setPoint(1, sf::Vector2f(0, 25));
            arrow.setPoint(2, sf::Vector2f(40, 50));
            arrow.setFillColor(sf::Color(100, 100, 100));
            arrow.setPosition(0, WINDOW_HEIGHT / 2.f - 25);
            window.draw(arrow);
        }
        // Права стрілка
        {
            sf::ConvexShape arrow;
            arrow.setPointCount(3);
            arrow.setPoint(0, sf::Vector2f(0, 0));
            arrow.setPoint(1, sf::Vector2f(40, 25));
            arrow.setPoint(2, sf::Vector2f(0, 50));
            arrow.setFillColor(sf::Color(100, 100, 100));
            arrow.setPosition(WINDOW_WIDTH - 40, WINDOW_HEIGHT / 2.f - 25);
            window.draw(arrow);
        }

        // Якщо показуємо результат, малюємо зелену галочку або червоний хрест по центру області кросворду
        if (showResult) {
            float centerX = WINDOW_WIDTH / 2.f;
            float centerY = (GRID_ROWS * CELL_SIZE) / 2.f;

            if (resultCorrect) {
                // Малювання зеленої галочки (вирівняної)
                sf::RectangleShape line1(sf::Vector2f(20, 8)); // коротша лінія для лівої частини
                line1.setFillColor(sf::Color(0, 200, 0));
                line1.setOrigin(0, 4); // Початок у лівому центрі
                line1.setPosition(centerX, centerY);
                line1.setRotation(45.f);
                window.draw(line1);

                sf::RectangleShape line2(sf::Vector2f(35, 8)); // довша лінія для правої частини
                line2.setFillColor(sf::Color(0, 200, 0));
                line2.setOrigin(0, 4);
                line2.setPosition(centerX + 13, centerY + 13); // зміщено для з'єднання з кінцем line1
                line2.setRotation(-45.f);
                window.draw(line2);
            } else {
                // Малювання червоного хреста (X)
                sf::RectangleShape cross1(sf::Vector2f(80, 8));
                cross1.setFillColor(sf::Color(200, 0, 0));
                cross1.setOrigin(40, 4); // Центр лінії
                cross1.setPosition(centerX, centerY);
                cross1.setRotation(45.f);
                window.draw(cross1);

                sf::RectangleShape cross2(sf::Vector2f(80, 8));
                cross2.setFillColor(sf::Color(200, 0, 0));
                cross2.setOrigin(40, 4);
                cross2.setPosition(centerX, centerY);
                cross2.setRotation(-45.f);
                window.draw(cross2);
            }
        }

        window.display();
    }

    return 0;
}