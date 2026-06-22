#pragma once

enum class PieceColor {
    White,
    Black
};

enum class PieceType {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
};

struct Position {
    int x;
    int y;
};

class Piece {
public:
    Piece(PieceColor color, PieceType type, Position pos) {
        m_color = color;
        m_type = type;
        m_position = pos;
    }

    PieceColor get_color() const {
        return m_color;
    }

    PieceType get_type() const {
        return m_type;
    }

private:
    PieceColor m_color;
    PieceType m_type;
    Position m_position;
};