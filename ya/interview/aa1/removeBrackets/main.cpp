#include <iostream>
#include <string>
#include <cassert>
#include <vector>

enum class State { 
    DEFAULT,
    COLON, 
    DASH,
    OPEN,
    CLOSED
};

std::string remove_brackets(std::string& input) {
    State state = State::DEFAULT;
    size_t currIndex = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        switch (state) {
        case State::DEFAULT: {
            if (c != ':') {
                input[currIndex++] = c;
            }
            else {
                state = State::COLON;
            }
            break;
        }
        case State::COLON: {
            if (c == '-') {
                state = State::DASH;
            }
            else {
                input[currIndex++] = ':';
                state = State::DEFAULT;
                --i;
            }
            break;
        }
        case State::DASH: {
            if (c == '(') {
                state = State::OPEN;
            } else if (c == ')') {
                state = State::CLOSED;
            }
            else {
                input[currIndex++] = ':';
                input[currIndex++] = '-';
                state = State::DEFAULT;
                --i;
            }
            break;
        }
        case State::OPEN: {
            if (c != '(') {
                state = State::DEFAULT;
                --i;
            }
            break;
        }
        case State::CLOSED: {
            if (c != ')') {
                state = State::DEFAULT;
                --i;
            }
            break;
        }
        }
    }
    input.resize(currIndex);
    return input;
}

int main()
{
    std::string input = "я работаю в яндексе :-)))";
    assert(remove_brackets(input) == std::string("я работаю в яндексе "));

    input = ":-)))";
    assert(remove_brackets(input) == "");

    input = "Aaaaa!!!!! :-))(())";
    // std::cout << remove_brackets(input) << std::endl;
    assert(remove_brackets(input) == "Aaaaa!!!!! (())");
    return 0;
}
