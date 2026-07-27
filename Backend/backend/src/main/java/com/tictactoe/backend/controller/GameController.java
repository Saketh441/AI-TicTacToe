package com.tictactoe.backend.controller;

import com.tictactoe.backend.entity.Game;
import com.tictactoe.backend.service.GameService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/game")
@CrossOrigin(origins = "*")
public class GameController {

    @Autowired
    private GameService gameService;

    @PostMapping("/save")
    public Game saveGame(@RequestBody Game game) {
        return gameService.saveGame(game);
    }

    @GetMapping("/all")
    public List<Game> getAllGames() {
        return gameService.getAllGames();
    }
}