#include <iostream>
#include <unordered_set>
#include <queue>

typedef union {
    int id = 0;
    char pitchers[3];
} state_u;

std::pair<int, int> get_variables(void)
{
    int limits[3];
    int goal[3];

    std::cout << "what are the capacity of each pitcher ? [ex: 16 9 7]" << std::endl;
    std::cout << ": ";
    std::cin >> limits[0] >> limits[1] >> limits[2];
    std::cout << "what are the goal of each pitcher ? [ex: 8 8 0]" << std::endl;
    std::cout << ": ";
    std::cin >> goal[0] >> goal[1] >> goal[2];
    std::cout << std::endl;

    state_u x = {.pitchers = {(char)limits[0], (char)limits[1], (char)limits[2]}};
    state_u y = {.pitchers = {(char)goal[0], (char)goal[1], (char)goal[2]}};

    return std::make_pair(x.id, y.id);
}

bool is_move_good(int from, int to, state_u state, state_u limits)
{
    return !(from == to || !state.pitchers[from] || state.pitchers[to] == limits.pitchers[to]);
}

bool check_victory(std::pair<int, std::string> state, state_u goal)
{
    state_u s = {state.first};

    if (s.id != goal.id)
        return false;

    std::cout << "The steps are:" << std::endl << state.second;

    return true;
}

int main(int ac, char **av)
{
    auto variables = get_variables();
    state_u limits = {variables.first};
    state_u goal = {variables.second};
    state_u initial_state = {.pitchers = {limits.pitchers[0]}};

    std::unordered_set<int> seen_states;
    std::queue<std::pair<int, std::string>> states;

    states.push({initial_state.id, ""});

    while (!states.empty()) {
        auto state = states.front(); states.pop();

        for (int from = 0; from < 3 ; from++)
            for (int to = 0; to < 3 ; to++) {

                auto new_state = state;
                state_u s = {state.first};

                if (!is_move_good(from, to, s, limits)) continue;

                int max = limits.pitchers[to] - s.pitchers[to];
                int r = max - s.pitchers[from] < 0 ? max : s.pitchers[from];

                s.pitchers[from] -= r;
                s.pitchers[to] += r;

                if (seen_states.find(s.id) != seen_states.end()) continue;
                seen_states.insert(s.id);

                new_state.first = s.id;
                new_state.second += std::to_string(from) + " > " + std::to_string(to) + "\n";

                if (check_victory(new_state, goal))
                    return (0);

                states.push(new_state);
            }
    }

    std::cout << "There's not a solution for this puzzle :(" << std::endl;
    return (1);
}