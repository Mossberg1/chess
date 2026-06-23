#include <iostream>
#include <string>
#include <stdexcept>

#include "board.hpp"
#include "piece.hpp"

void draw_piece(const Piece& piece);
void draw_board(Board& board);
void switch_player(PieceColor& color);
std::string to_string(PieceColor color);
Move get_move(PieceColor current_player);

int main() {
    Board* board = new Board();

    PieceColor current_player = PieceColor::White;

    std::cout << "\033[?25l"; 
    std::cout << "\033[2J";

    while (!board->winner().has_value()) {
        std::cout << "\033[2J\033[H";
        draw_board(*board);

        Move move = get_move(current_player);

        if (board->is_legal(move)) {
            board->apply(move);
        }
        else {
            std::cout << "Not a valid move. Press enter to try again.";
            std::cin.ignore();
            continue;
        }

        switch_player(current_player);
    }

    std::cout << "\033[?25h";

    return 0;
}

void draw_board(Board& board) {
    std::cout << "\n";
    
    for (int y = 7; y >= 0; --y) {
        std::cout << y + 1 << " "; 
        
        for (int x = 0; x < 8; ++x) {
            std::optional<Piece> square = board.get_piece(x, y);
            
            if (square.has_value()) {
                std::cout << "[";
                draw_piece(square.value());
                std::cout << "]";
            } else {
                std::cout << "[ ]";
            }
        }
        std::cout << "\n";
    }
    
    std::cout << "   a  b  c  d  e  f  g  h\n\n";
}

void draw_piece(const Piece& piece) {
    char c = ' ';

    switch (piece.get_type()) {
        case PieceType::King:   c = 'K'; break;
        case PieceType::Queen:  c = 'Q'; break;
        case PieceType::Rook:   c = 'R'; break;
        case PieceType::Bishop: c = 'B'; break;
        case PieceType::Knight: c = 'N'; break;
        case PieceType::Pawn:   c = 'P'; break;
    }
    
    // Make Black pieces lowercase
    if (piece.get_color() == PieceColor::Black) {
        c = std::tolower(c);
    }

    std::cout << c;
}

void switch_player(PieceColor& color) {
    color = color == PieceColor::White ? PieceColor::Black : PieceColor::White;
}

Position parse_position(std::string move) {
    if (move.length() != 2) {
        throw std::invalid_argument("Move must have exactly two characters.");
    }

    int x = move[0] - 'a';
    int y = move[1] - '1';

    return { x, y };
}

std::string to_string(PieceColor color) {
    return color == PieceColor::White ? "White" : "Black";
}

Move get_move(PieceColor current_player) {
    bool valid_move = false;
    Position from;
    Position to;
    while (!valid_move) {
        try {
            std::string from_input;
            std::cout << "Select piece: "<< "(" << to_string(current_player) << "): ";
            std::cin >> from_input;
            from = parse_position(from_input);

            std::string to_input;
            std::cout << "Move to: (" << to_string(current_player) << "): ";
            std::cin >> to_input;
            to = parse_position(to_input);

            valid_move = true;
        }
        catch (std::invalid_argument) {
            std::cout << "Move out of bounds. Press enter to try again.";
            std::cin.ignore();
        }
    }   
    return Move { from, to };
}