SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";

CREATE DATABASE IF NOT EXISTS `a_chat` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci;
USE `a_chat`;

CREATE TABLE `messages` (
  `id` int NOT NULL,
  `author` bigint DEFAULT NULL,
  `text` varchar(3000) NOT NULL,
  `time` bigint NOT NULL,
  `attachments` text,
  `isSticker` tinyint NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `users` (
  `id` bigint NOT NULL,
  `user_login` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `user_password` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `display_name` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `user_rank` int NOT NULL,
  `user_score` int NOT NULL,
  `next_score` int NOT NULL,
  `money` int NOT NULL,
  `gold` int NOT NULL,
  `admin_rank` int NOT NULL,
  `avatar_path` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

INSERT INTO `users` (`id`, `user_login`, `user_password`, `display_name`, `user_rank`, `user_score`, `next_score`, `money`, `gold`, `admin_rank`, `avatar_path`) VALUES
(1, 'amalgama', 'xxXX6677', 'Amalgama', 5, 3830, 100, 1350, 100, 2, NULL),
(2, 'officer', 'xxXX6677', 'Officer', 1, 120, 100, 350, 10, 1, NULL);


ALTER TABLE `messages`
  ADD PRIMARY KEY (`id`),
  ADD KEY `author_idx` (`author`);

ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `login_UNIQUE` (`user_login`);


ALTER TABLE `messages`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

ALTER TABLE `users`
  MODIFY `id` bigint NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;


ALTER TABLE `messages`
  ADD CONSTRAINT `author` FOREIGN KEY (`author`) REFERENCES `users` (`id`) ON DELETE SET NULL;
COMMIT;
