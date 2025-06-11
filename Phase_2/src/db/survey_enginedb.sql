-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 12, 2025 at 01:33 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `survey_enginedb`
--

-- --------------------------------------------------------

--
-- Table structure for table `answer`
--

CREATE TABLE `answer` (
  `AnswerID` int(10) NOT NULL,
  `Text` varchar(500) DEFAULT NULL,
  `QuestionID` int(7) DEFAULT NULL,
  `ResponseID` int(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `answer`
--

INSERT INTO `answer` (`AnswerID`, `Text`, `QuestionID`, `ResponseID`) VALUES
(1, 'Very good', 1, 2),
(2, 'Good', 1, 3),
(3, 'Good', 1, 4),
(4, 'No comments :D', 2, 5),
(5, 'Very bad', 1, 6),
(6, 'I am Greece and German', 2, 7),
(7, 'No', 4, 8),
(8, 'Because I want to get married with Ajia', 5, 8),
(9, 'Regular', 1, 9),
(10, 'Bad', 6, 10),
(11, 'No', 4, 11),
(12, 'I am sad because I feel lonely', 5, 11),
(13, 'Yes', 4, 12),
(14, 'The semester is almost over', 5, 12),
(15, 'No', 7, 13),
(16, 'Because I think it is stupid', 8, 13),
(17, 'No', 7, 14),
(18, 'I only like electro music', 8, 14),
(19, 'No', 9, 15),
(20, 'I don\'t understand Spanish', 10, 15),
(21, 'No', 4, 16),
(22, 'I don\'t love myself', 5, 16),
(23, 'Yes', 7, 17),
(24, 'Me gusta el reggaeton', 8, 17);

-- --------------------------------------------------------

--
-- Table structure for table `choice`
--

CREATE TABLE `choice` (
  `ChoiceID` int(10) NOT NULL,
  `Text` varchar(255) DEFAULT NULL,
  `QuestionID` int(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `choice`
--

INSERT INTO `choice` (`ChoiceID`, `Text`, `QuestionID`) VALUES
(1, 'Very good', 1),
(2, 'Good', 1),
(3, 'Regular', 1),
(4, 'Bad', 1),
(5, 'Very bad', 1),
(6, 'Lamine Yamal', 3),
(7, 'Raphinha', 3),
(8, 'Lewandowski', 3),
(9, 'Cubarsi', 3),
(10, 'Yes', 4),
(11, 'No', 4),
(12, 'Good', 6),
(13, 'Regular', 6),
(14, 'Bad', 6),
(15, 'Yes', 7),
(16, 'No', 7),
(17, 'Yes', 9),
(18, 'No', 9),
(19, 'Simon', 11),
(20, 'Nel pastel', 11),
(21, 'Yes', 13),
(22, 'No', 13);

-- --------------------------------------------------------

--
-- Table structure for table `question`
--

CREATE TABLE `question` (
  `QuestionID` int(10) NOT NULL,
  `Text` varchar(500) DEFAULT NULL,
  `isMultipleChoice` tinyint(1) DEFAULT NULL,
  `SurveyID` int(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `question`
--

INSERT INTO `question` (`QuestionID`, `Text`, `isMultipleChoice`, `SurveyID`) VALUES
(1, 'Rate this', 1, 1),
(2, 'Any comments?', 0, 2),
(3, 'Who\'s your favorite player?', 1, 3),
(4, 'Are you happy?', 1, 4),
(5, 'Justify your previous answer', 0, 4),
(6, 'Rate the service', 1, 5),
(7, 'Do you like the music?', 1, 6),
(8, 'Why?', 0, 6),
(9, 'Do you like Mocedades?', 1, 7),
(10, 'Why or why not?', 0, 7),
(11, 'Te gusta el reggaeton?', 1, 8),
(12, 'Por que hpta???', 0, 8),
(13, 'Will Savvas marry Ajia', 1, 9),
(14, 'Why you think so?', 0, 9),
(15, 'Why do you think Greece is the best nation in the world', 0, 10),
(16, 'I just want to test something', 0, 11),
(17, 'I just want to test something', 0, 12),
(18, 'I just want to test something', 0, 12),
(19, 'I just want to test something', 0, 13);

-- --------------------------------------------------------

--
-- Table structure for table `response`
--

CREATE TABLE `response` (
  `ResponseID` int(10) NOT NULL,
  `UserID` int(10) DEFAULT NULL,
  `SurveyID` int(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `response`
--

INSERT INTO `response` (`ResponseID`, `UserID`, `SurveyID`) VALUES
(2, 1, 1),
(3, 1, 1),
(4, 1, 1),
(5, 1, 2),
(6, 2, 1),
(7, 3, 2),
(8, 3, 4),
(9, 1, 1),
(10, 1, 5),
(11, 1, 4),
(12, 2, 4),
(13, 1, 6),
(14, 6, 6),
(15, 6, 7),
(16, 4, 4),
(17, 4, 6);

-- --------------------------------------------------------

--
-- Table structure for table `survey`
--

CREATE TABLE `survey` (
  `SurveyID` int(10) NOT NULL,
  `Title` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `survey`
--

INSERT INTO `survey` (`SurveyID`, `Title`) VALUES
(1, 'Feedback'),
(2, 'Comments'),
(3, 'FC Barcelona opinion'),
(4, 'Mindset'),
(5, 'Math lab feedback'),
(6, 'Baki\'s music opinion'),
(7, 'Mocedades opinion'),
(8, 'Opinion sobre el reggaeton'),
(9, 'Savvas\'s future'),
(10, 'Greece opinion'),
(11, 'Testing something'),
(12, 'Testing something'),
(13, 'Testing something');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `UserID` int(10) NOT NULL,
  `Name` varchar(50) DEFAULT NULL,
  `Password` varchar(51) NOT NULL,
  `isAdmin` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`UserID`, `Name`, `Password`, `isAdmin`) VALUES
(1, 'brysach', 'rcc', 1),
(2, 'michael', 'teacher', 0),
(3, 'savvas', 'greece', 1),
(4, 'jacob', 'china', 0),
(5, 'jesus', 'mexico', 0),
(6, 'julian', 'pineapple', 0),
(7, 'mocedades', 'musica', 0),
(8, 'heather', 'england', 0),
(9, 'tom123', 'jerryY123!@', 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `answer`
--
ALTER TABLE `answer`
  ADD PRIMARY KEY (`AnswerID`);

--
-- Indexes for table `choice`
--
ALTER TABLE `choice`
  ADD PRIMARY KEY (`ChoiceID`);

--
-- Indexes for table `question`
--
ALTER TABLE `question`
  ADD PRIMARY KEY (`QuestionID`);

--
-- Indexes for table `response`
--
ALTER TABLE `response`
  ADD PRIMARY KEY (`ResponseID`);

--
-- Indexes for table `survey`
--
ALTER TABLE `survey`
  ADD PRIMARY KEY (`SurveyID`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`UserID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `answer`
--
ALTER TABLE `answer`
  MODIFY `AnswerID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;

--
-- AUTO_INCREMENT for table `choice`
--
ALTER TABLE `choice`
  MODIFY `ChoiceID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT for table `question`
--
ALTER TABLE `question`
  MODIFY `QuestionID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;

--
-- AUTO_INCREMENT for table `response`
--
ALTER TABLE `response`
  MODIFY `ResponseID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT for table `survey`
--
ALTER TABLE `survey`
  MODIFY `SurveyID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `UserID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
