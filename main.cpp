#include <iostream>
#include <unordered_set>
#include <queue>

typedef union {
    int id = 0;
    char pitchers[3];
} state_u;

std::pair<int, int> get_variables(int ac, char **av)
{
    if (ac != 7)
        throw std::runtime_error("bad arguments");

    state_u x = {.pitchers = {(char)std::atoi(av[1]), (char)std::atoi(av[2]), (char)std::atoi(av[3])}};
    state_u y = {.pitchers = {(char)std::atoi(av[4]), (char)std::atoi(av[5]), (char)std::atoi(av[6])}};

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

bool algorithm(int from, int to, state_u limits, state_u goal, std::queue<std::pair<int, std::string>> &states,
    std::unordered_set<int> &seen_states, std::pair<int, std::string> &state)
{

    auto new_state = state;
    state_u s = {state.first};

    if (!is_move_good(from, to, s, limits)) return (false);

    int max = limits.pitchers[to] - s.pitchers[to];
    int r = max - s.pitchers[from] < 0 ? max : s.pitchers[from];

    s.pitchers[from] -= r;
    s.pitchers[to] += r;

    if (seen_states.find(s.id) != seen_states.end()) return (false);
    seen_states.insert(s.id);

    new_state.first = s.id;
    new_state.second += std::to_string(from) + " > " + std::to_string(to) + "\n";

    if (check_victory(new_state, goal))
        return (true);

    states.push(new_state);
    return (false);
}

int main(int ac, char **av)
{
    std::pair<int, int> variables = get_variables(ac, av);
    state_u limits = {variables.first};
    state_u goal = {variables.second};

    std::unordered_set<int> seen_states;
    std::queue<std::pair<int, std::string>> states;

    states.push({limits.pitchers[0], ""});

    while (!states.empty()) {
        auto state = states.front(); states.pop();

        for (int from = 0; from < 3 ; from++)
            for (int to = 0; to < 3 ; to++)
                if (algorithm(from, to, limits, goal, states, seen_states, state))
                    return (0);
    }

    std::cout << "There's not a solution for this puzzle :(" << std::endl;
    return (1);
}