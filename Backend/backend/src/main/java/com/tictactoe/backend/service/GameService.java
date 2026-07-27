package com.tictactoe.backend.service;

import com.tictactoe.backend.entity.Game;
import com.tictactoe.backend.repository.GameRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class GameService {

    @Autowired
    private GameRepository gameRepository;

    // Save game result
    public Game saveGame(Game game) {
        return gameRepository.save(game);
    }

    // Get all game results
    public List<Game> getAllGames() {
        return gameRepository.findAll();
    }
}