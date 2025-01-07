# Multi-Threaded Poker Simulator

## Overview
The Multi-Threaded Poker Simulator is a highly performant, object-oriented poker game designed to simulate real-world gameplay mechanics with customizable parameters and advanced features. Built using C++ with a Qt-based front end, the simulator delivers an immersive, interactive experience for players and developers alike. Incorporating AI-driven bots, real-time player statistics, and enhanced user controls, this project balances robust gameplay, modular architecture, and replayability for both casual players and poker enthusiasts.

## Key Features

### 1. **Customizable Game Parameters**
- Dynamically configure the number of players (2-8) and initial chip counts using flexible parameter-passing mechanisms.
- Seats for players are dynamically positioned around the table.
- Players can set game-specific parameters at the start, allowing tailored gameplay experiences for different skill levels and scenarios.

### 2. **AI-Driven Opponents**
- Implemented advanced AI bots with strategic decision-making algorithms to simulate realistic player behavior.
- Bots analyze game state, betting patterns, and hand strength to calculate suggested actions such as *Check*, *Raise*, *Call*, or *Fold*.
- Designed AI to vary difficulty levels, providing diverse gameplay experiences that challenge both new and experienced players.

### 3. **Real-Time Player Statistics**
- Track and display key player metrics during gameplay, including:
  - Current chip count
  - Win/loss ratios
  - Betting patterns
  - Total Profit
- Statistics are updated dynamically to reflect real-time game progress, providing insights into player performance.

### 4. **Action Suggestions**
- Added a *Calculate Action* button that recommends optimal moves based on player hand strength and the game state.
- Leverages probability-based analysis and decision trees to help players improve their strategy.

### 5. **Qt-Based User Interface**
- Developed a clean, visually appealing, and intuitive front-end using **Qt**.
- Key UI components include:
  - Dynamic player panels showing chip count, bets, pot count, community cards, and player cards.
  - Clear and responsive buttons for player actions (e.g., Check, Bet, Raise, Fold)
- Designed for ease of use, making gameplay accessible for new players and smooth for experienced users.

### 6. **Replayability and Reset Options**
- Implemented a *Reset Game* feature, allowing players to restart a session within the Settings menu.
- Ensures replayability by enabling players to experiment with different strategies, opponents, and scenarios.
- Randomized card shuffling and AI behaviors provide a fresh experience with every game.

### 7. **Tutorial for New Players**
- Added a a tutorial screen in the main menu to help new players understand the rules and mechanics of poker.
- On screen displays walk players through gameplay, including:
  - Basic poker rules and terminology
  - How betting, calling, and folding work
  - How to interpret player hands and game states
- Designed for beginner-friendly onboarding without overwhelming new users.

### 8. **Concurrency and Performance**
- Multi-threaded architecture ensures smooth and responsive gameplay, even with multiple AI players.
- Efficient resource management allows simultaneous game state updates, UI rendering, and AI calculations.
- Ensures minimal latency and optimal performance across different platforms.

### 9. **Modular Design**
- Leveraged object-oriented programming (OOP) principles and design patterns for scalability and maintainability.
- Features modular components for AI logic, UI rendering, and game rules, making it easy to add or modify functionality.
- Supports future enhancements like additional poker variants, improved AI strategies, or multiplayer options.


## How to Play
1. Launch the game and configure the desired parameters (number of players, starting chips, etc.).
2. Look at the tutorial in the Main Menu to learn the rules.
3. Follow the prompts and action buttons to make decisions each round:
   - *Check*: Pass the action to the next player.
   - *Raise*: Wager chips based on hand strength.
   - *Call*: Match the current bet.
   - *Fold*: Exit the current hand.
4. Use the *Calculate Action* button for AI-recommended moves.
5. Track player stats and gameplay progress in real time.
6. Use the *Reset Game* option in Settings to restart a new session.

## Technologies Used
- **Programming Language**: C++
- **Framework**: Qt (UI Development)
- **Version Control**: Git
- **Methodology**: Agile development with iterative sprints

## Contributors
- **Sean Clayton**
- **Ivan Wong**
- **Sunil Jain**
- **Kai Lindskog-Coffin**
- **Jordan Cowan**
- **Tristan Vosburg**
- **Maximilian Wolfe**