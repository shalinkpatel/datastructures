#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>
using namespace std;
typedef vector<int> VI;
typedef pair<double, VI> PDVI;
typedef pair<int, VI> PIVI;
typedef vector<PIVI> VPIVI;
typedef vector<PDVI> VPDVI;

void print_hand(const VI& hand) {
    for (int i = 0; i < 5; ++i)
        cout << hand[i] << " ";
    cout << endl;
}



bool is_flush(const VI& h) {
    for (int i = 0; i < 4; ++i)
        if (h[i] % 4 != h[i + 1] % 4)
            return false;
    return true;
}


int is_straight(const VI& h) {
    // 0 = not straight
    // 1 = straight
    // 2 = straight (low ace)
    if (h[4] / 4 == 12) { // check for Ace
        bool a = (h[0] / 4 == 0) && (h[1] / 4 == 1) && (h[2] / 4 == 2) && (h[3] / 4 == 3); // ace low
        bool b = (h[0] / 4 == 8) && (h[1] / 4 == 9) && (h[2] / 4 == 10) && (h[3] / 4 == 11); // ace high
        if (a)
            return 2;
        else if (b)
            return 1;
        else
            return 0;
    } else {
        for (int i = 0; i < 4; ++i)
            if (h[i] / 4 != (h[i + 1] / 4) - 1)
                return 0;
        return 1;
    }
}

bool is_ace_low(const VI& hand) {
    return is_straight(hand) == 2;
}


bool is_full_house(const VI& h) {
    bool a = (h[0] / 4 == h[1] / 4) && (h[1] / 4 == h[2] / 4) && (h[3] / 4 == h[4] / 4);
    bool b = (h[0] / 4 == h[1] / 4) && (h[2] / 4 == h[3] / 4) && (h[3] / 4 == h[4] / 4);
    return (a || b);
}


bool is_four_kind(const VI& h) {
    for (int i = 0; i < 2; ++i)
        if ((h[i] / 4 == h[i + 1] / 4) && (h[i + 1] / 4 == h[i + 2] / 4) && (h[i + 2] / 4 == h[i + 3] / 4))
            return true;
    return false;
}


bool is_three_kind(const VI& h) {
    for (int i = 0; i < 3; ++i)
        if ((h[i] / 4 == h[i + 1] / 4) && (h[i + 1] / 4 == h[i + 2] / 4))
            return true;
    return false;
}


int get_num_pairs(const VI& h) {
    int num_pairs = 0;
    for (int i = 0; i < 5; i++) {
        if (h[i] / 4 == h[i + 1] / 4) {
            ++num_pairs;
            ++i;
        }
    }
    return num_pairs;
}


int get_hand_type(const VI& hand) {
    bool flush = is_flush(hand);
    int straight = is_straight(hand);
    if (flush && straight)
        return 8;
    else if (flush)
        return 5;
    else if (straight)
        return 4;
    else if (is_four_kind(hand))
        return 7;
    else if (is_full_house(hand))
        return 6;
    else if (is_three_kind(hand))
        return 3;
    return get_num_pairs(hand);
}


double get_hand_val(const VI& h, const int& type) {
    // generates a value to each hand (base 13) 
    // based on hand type and lexicographic order
    double val = type * 371293;
    if (type == 8 || type == 4) {   // straight flush and straight
        // only highest card matters
        if (is_ace_low(h))
            val += h[3] / 4;
        else
            val += h[4] / 4;
    } else if (type == 7) { // four of a kind
        // find the 2 different cards
        val += h[2] / 4 * 13;
        if (h[0] / 4 == h[1] / 4)
            val += h[4] / 4;
        else
            val += h[0] / 4;
    }  else if (type == 6) {    // full house
        val += h[2] / 4 * 13;
        if (h[0] / 4 == h[1] / 4 && h[1] / 4 == h[2] / 4)
            val += h[3] / 4;
        else
            val += h[0] / 4;
    } else if (type == 3) { // three of a kind
        val += h[2] / 4 * 169;
        if (h[0] / 4 == h[2] / 4)
            val += h[4] / 4 * 13 + h[3] / 4;
        else if (h[1] / 4 == h[3] / 4)
            val += h[4] / 4 * 13 + h[0] / 4;
        else
            val += h[1] / 4 * 13 + h[0] / 4;
    } else if (type == 2) { // two pairs
        if ((h[0] / 4 == h[1] / 4) && (h[2] / 4 == h[3] / 4))
            val += h[2] / 4 * 169 + h[0] / 4 * 13 + h[4] / 4;
        else if ((h[0] / 4 == h[1] / 4) && (h[3] / 4 == h[4] / 4))
            val += h[3] / 4 * 169 + h[0] / 4 * 13 + h[2] / 4;
        else
            val += h[3] / 4 * 169 + h[1] / 4 * 13 + h[0] / 4;
    } else if (type == 1) { // one pair
        if (h[0] / 4 == h[1] / 4)
            val += h[0] / 4 * 2197 + h[4] / 4 * 169 + h[3] / 4 * 13 + h[2] / 4;
        else if (h[1] / 4 == h[2] / 4)
            val += h[1] / 4 * 2197 + h[4] / 4 * 169 + h[3] / 4 * 13 + h[0] / 4;
        else if (h[2] / 4 == h[3] / 4)
            val += h[2] / 4 * 2197 + h[4] / 4 * 169 + h[1] / 4 * 13 + h[0] / 4;
        else
            val += h[3] / 4 * 2197 + h[2] / 4 * 169 + h[1] / 4 * 13 + h[0] / 4;
    } else {    // flush and high card
        val += h[4] / 4 * 28561 + h[3] / 4 * 2197 + h[2] / 4 * 169 + h[1] / 4 * 13 + h[0] / 4;
    }
    return val;
}


void sort_hand(VI& hand) {
    for(int i = 1; i < 5; ++i)
        for(int j = i; j > 0 && hand[j - 1] > hand[j]; --j)
            swap(hand[j], hand[j - 1]);
}


double probability(const int& type) {
    if (type == 8)
        return 0.0015;
    else if (type == 7)
        return 0.0240;
    else if (type == 6)
        return 0.1441;
    else if (type == 5)
        return 0.1965;
    else if (type == 4)
        return 0.3925;
    else if (type == 3)
        return 2.1128;
    else if (type == 2)
        return 4.7539;
    else if (type == 1)
        return 42.2569;
    return 50.1177;
}


bool is_card_in_hand(const VI& h, const int& card) {
    return card == h[0] or card == h[1] or card == h[2] or card == h[3] or card == h[4];
}


// PIVI exchange_one(const VI& hand, const int& index, ) {
//     PIVI max_pair;
//     VI temp_hand(5);
//     for (int i = 0; i < 5; ++i)
//         if (i != index)
//             temp_hand[i] = hand[i];

//     for (int i = 0; i < 52; ++i) {
//         if (is_card_in_hand(hand, i))
//             continue;
//         temp_hand[index] = i;
//         sort_hand(temp_hand);
//         int temp_type = get_hand_type(temp_hand);
//         int temp_val = get_hand_val(temp_hand, temp_type);
//         temp_val *= probability(temp_type);
//         if (temp_val >= max_pair.first)
//             max_pair = make_pair(temp_val, VI{index});
//     }
//     return max_pair;
// }


// PIVI exchange_two(const VI&hand, const VI& indices) {
//     PIVI max_pair;
//     VI temp_hand(5);
//     for (int i = 0; i < 5; ++i)
//         if (i != indices[0] && i != indices[1])
//             temp_hand[i] = hand[i];
    
//     for (int i = 0; i < 52; ++i) {
//         if (is_card_in_hand(hand, i))
//             continue;
//         temp_hand[indices[0]] = i;
//         for (int j = i + 1; j < 52; ++j) {
//             if (is_card_in_hand(hand, j))
//                 continue;
//             temp_hand[indices[1]] = j;
//             sort_hand(temp_hand);
//             int temp_type = get_hand_type(temp_hand);
//             int temp_val = get_hand_val(temp_hand, temp_type);
//             temp_val *= probability(temp_type);
//             if (temp_val >= max_pair.first)
//                 max_pair = make_pair(temp_val, indices);
//         }
//     }
//     return max_pair;
// }


// PIVI exchange_three(const VI&hand, const VI& indices) {
//     PIVI max_pair;
//     VI temp_hand(5);
//     for (int i = 0; i < 5; ++i)
//         if (i != indices[0] && i != indices[1] && i != indices[2])
//             temp_hand[i] = hand[i];
    
//     for(int i = 0; i < 52; ++i) {
//         if (is_card_in_hand(hand, i))
//             continue;
//         temp_hand[indices[0]] = i;
//         for (int j = i + 1; j < 52; ++j) {
//             if (is_card_in_hand(hand, j))
//                 continue;
//             temp_hand[indices[1]] = j;
//             for (int k = j + 1; k < 52; ++k) {
//                 if (is_card_in_hand(hand, k))
//                     continue;
//                 temp_hand[indices[2]] = k;
//                 sort_hand(temp_hand);
//                 int temp_type = get_hand_type(temp_hand);
//                 int temp_val = get_hand_val(temp_hand, temp_type);
//                 temp_val *= probability(temp_type);
//                 if (temp_val >= max_pair.first)
//                     max_pair = make_pair(temp_val, indices);
//             }
//         }
//     }
//     return max_pair;
// }

PDVI exchange_one(const VI& hand, const int& index, const double& val) {
    VI temp_hand(5);
    for (int i = 0; i < 5; ++i)
        if (i != index)
            temp_hand[i] = hand[i];
    PDVI move(val, VI{index});
    for (int i = 0; i < 52; ++i) {
        if (is_card_in_hand(hand, i))
            continue;
        temp_hand[index] = i;
        sort_hand(temp_hand);
        int temp_type = get_hand_type(temp_hand);
        int temp_val = get_hand_val(temp_hand, temp_type);
        if (temp_val >= val)
            move.first += (1.0 / 47) * temp_val;
        else
            move.first -= (1.0 / 47) * temp_val;
        // if (temp_val >= val)
        //     pos.push_back(make_pair(temp_val, VI{index}));
        // else
        //     neg.push_back(make_pair(temp_val, VI{index}));
    }
    return move;
}


PDVI exchange_two(const VI&hand, const VI& indices, const double& val) {
    VI temp_hand(5);
    for (int i = 0; i < 5; ++i)
        if (i != indices[0] && i != indices[1])
            temp_hand[i] = hand[i];
    PDVI move(val, indices);
    
    for (int i = 0; i < 52; ++i) {
        if (is_card_in_hand(hand, i))
            continue;
        temp_hand[indices[0]] = i;
        for (int j = i + 1; j < 52; ++j) {
            if (is_card_in_hand(hand, j))
                continue;
            temp_hand[indices[1]] = j;
            sort_hand(temp_hand);
            int temp_type = get_hand_type(temp_hand);
            int temp_val = get_hand_val(temp_hand, temp_type);
            if (temp_val >= val)
                move.first += (1.0 / 47) * (1.0 / 46) * temp_val;
            else
                move.first -= (1.0 / 47) * (1.0 / 46) * temp_val;
            // if (temp_val >= val)
            //     pos.push_back(make_pair(temp_val, indices));
            // else
            //     neg.push_back(make_pair(temp_val, indices));
        }
    }
    return move;
}


PDVI exchange_three(const VI&hand, const VI& indices, const double& val) {
    VI temp_hand(5);
    for (int i = 0; i < 5; ++i)
        if (i != indices[0] && i != indices[1] && i != indices[2])
            temp_hand[i] = hand[i];
    PDVI move(val, indices);
    for(int i = 0; i < 52; ++i) {
        if (is_card_in_hand(hand, i))
            continue;
        temp_hand[indices[0]] = i;
        for (int j = i + 1; j < 52; ++j) {
            if (is_card_in_hand(hand, j))
                continue;
            temp_hand[indices[1]] = j;
            for (int k = j + 1; k < 52; ++k) {
                if (is_card_in_hand(hand, k))
                    continue;
                temp_hand[indices[2]] = k;
                sort_hand(temp_hand);
                int temp_type = get_hand_type(temp_hand);
                int temp_val = get_hand_val(temp_hand, temp_type);
                if (temp_val >= val)
                    move.first += (1.0 / 47) * (1.0 / 46) * (1.0 / 45) * temp_val;
                else
                    move.first -= (1.0 / 47) * (1.0 / 46) * (1.0 / 45) * temp_val;
                // if (temp_val >= val)
                //     pos.push_back(make_pair(temp_val, indices));
                // else
                //     neg.push_back(make_pair(temp_val, indices));
            }
        }
    }
    return move;
}


int main() {
    while(true){
    VI hand(5);
    for(int i = 0; i < 5; ++i)
        cin >> hand[i];
    sort_hand(hand);

    int type = get_hand_type(hand);
    double val = get_hand_val(hand, type);
    // cout << "Type: " << type << endl;
    // cout << "Value: " << val << endl;
    VPDVI moves{make_pair(val, VI(0))};

    for (int i = 0; i < 5; ++i) {
        moves.push_back(exchange_one(hand, i, val));
        for (int j = i + 1; j < 5; ++j) {
            moves.push_back(exchange_two(hand, VI{i, j}, val));
            for (int k = j + 1; k < 5; ++k) {
                moves.push_back(exchange_three(hand, VI{i, j, k}, val));
            }
        }
    }

    // for (PDVI move : moves) {
    //     cout << move.first << ": ";
    //     for (int i : move.second) {
    //         cout << i << " ";
    //     }
    //     cout << endl;
    // }
    sort(moves.begin(), moves.end());
    PDVI best_move = moves.back();
    cout << best_move.second.size() << " ";
    for (int ci : best_move.second)
        cout << hand[ci] << " ";
    cout << endl;}
}
