#include <vector>

#include "board.hpp"

std::vector<Move> legal_moves(const Board& board, const Piece& piece);

void Board::apply(const Move& move) {
    m_board[move.to.x][move.to.y] = m_board[move.from.x][move.from.y];
    m_board[move.to.x][move.to.y]->set_position(move.to.x, move.to.y);
    m_board[move.from.x][move.from.y] = std::nullopt;
}

bool Board::is_legal(const Move& move) {
    auto piece = get_piece(move.from.x, move.from.y);
    if (!piece) {
        return false;
    }

    auto moves = legal_moves(*this, *piece);
    
    for (const auto& m : moves) {
        if (m.to.x == move.to.x && m.to.y == move.to.y) {
            return true;
        }
    }

    return false;
}

std::optional<PieceColor> Board::winner() {
    bool white_king = false, black_king = false;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            auto piece = get_piece(x, y);
            if (piece && piece->get_type() == PieceType::King) {
                if (piece->get_color() == PieceColor::White) {
                    white_king = true;
                }
                else {
                    black_king = true;
                }
            }
        }
    }

    if (!white_king) {
        return PieceColor::Black;
    }

    if (!black_king) {
        return PieceColor::White;
    }

    return std::nullopt;
}

bool out_of_bounds(int x, int y) {
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return true;
    }

    return false;
}

std::vector<std::pair<int, int>> get_move_pattern(const Piece& piece) {
    switch (piece.get_type()) {
        case PieceType::Rook:
            return {{1,0},{-1,0},{0,1},{0,-1}};
        case PieceType::Bishop:
            return {{1,1},{-1,1},{1,-1},{-1,-1}};
        case PieceType::Queen:
            return {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};
        case PieceType::King:
            return {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};
        case PieceType::Knight:
            return {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{-1,2},{1,-2},{-1,-2}};
        case PieceType::Pawn:
            return {};
    }
    
    __builtin_unreachable();
}

std::vector<Move> handle_pawn_move_pattern(const Board& board, const Piece& piece) {
    bool is_white = piece.get_color() == PieceColor::White;
    int dir = is_white ? 1 : -1;
    int start_row = is_white ? 1 : 6;
    auto pos = piece.get_position();

    std::vector<Move> moves;

    if (!out_of_bounds(pos.x, pos.y + dir) && !board.get_piece(pos.x, pos.y + dir)) {
        moves.push_back({{pos.x, pos.y}, {pos.x, pos.y + dir}});
    }

    if (pos.y == start_row && !board.get_piece(pos.x, pos.y + dir) && !board.get_piece(pos.x, pos.y + 2 * dir)) {
        moves.push_back({{pos.x, pos.y}, {pos.x, pos.y + 2 * dir}});
    }

    for (int dx : {-1, 1}) {
        if (out_of_bounds(pos.x + dx, pos.y + dir)) continue;
        auto target = board.get_piece(pos.x + dx, pos.y + dir);
        if (target && target->get_color() != piece.get_color()) {
            moves.push_back({{pos.x, pos.y}, {pos.x + dx, pos.y + dir}});
        }
    }

    return moves;
}

std::vector<Move> legal_moves(const Board& board, const Piece& piece) {
    std::vector<Move> moves;
    auto type = piece.get_type();

    if (type == PieceType::Pawn) {
        return handle_pawn_move_pattern(board, piece);
    }

    auto pos = piece.get_position();
    auto directions = get_move_pattern(piece);

    int max_steps = type == PieceType::King || type == PieceType::Knight ? 1 : 8;

    for (auto [dx, dy] : directions) {
        for (int step = 1; step < max_steps; step++) {
            int nx = pos.x + dx * step;
            int ny = pos.y + dy * step;

            if (out_of_bounds(nx, ny)) {
                break;
            }

            auto occupant = board.get_piece(nx, ny);

            if (occupant) {
                if (occupant->get_color() != piece.get_color()) {
                    moves.push_back({{pos.x, pos.y}, {nx, ny}});
                }
                break;
            }

            moves.push_back({{pos.x, pos.y}, {nx, ny}});
        }
    }

    return moves;
}