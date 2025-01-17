CREATE DATABASE  IF NOT EXISTS `sge_nexuserp` /*!40100 DEFAULT CHARACTER SET utf8 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `sge_nexuserp`;
-- MySQL dump 10.13  Distrib 8.0.27, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: sge_nexuserp
-- ------------------------------------------------------
-- Server version	8.0.27

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `erp_devices`
--

DROP TABLE IF EXISTS `erp_devices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `erp_devices` (
  `id` int NOT NULL AUTO_INCREMENT,
  `mac` varchar(12) COLLATE utf8mb4_spanish_ci NOT NULL COMMENT 'mac del dispositivo de sondeo y riego',
  `latitude` decimal(18,12) NOT NULL COMMENT 'latitud gps',
  `longitude` decimal(18,12) NOT NULL COMMENT 'longitud gps',
  `frequency` int NOT NULL DEFAULT '10' COMMENT 'frecuencia de actualizacion datos reportados. Por defecto 10 min',
  `last_connection` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `INDEX_MAC` (`mac`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_spanish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `erp_devices`
--

LOCK TABLES `erp_devices` WRITE;
/*!40000 ALTER TABLE `erp_devices` DISABLE KEYS */;
INSERT INTO `erp_devices` VALUES (1,'841FE7164BAF',37.188170000000,-3.606670000000,10,'2023-04-14 18:22:19');
/*!40000 ALTER TABLE `erp_devices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `erp_mesures`
--

DROP TABLE IF EXISTS `erp_mesures`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `erp_mesures` (
  `id_device` int NOT NULL COMMENT 'equipo desde el que se realiza la medicion',
  `id_sensor` int NOT NULL COMMENT 'Numero de entrada del sensor 1 ,2 ,3 ,4....',
  `id_sensor_type` int NOT NULL COMMENT 'tipo de media: gps,temperatura, humedad...',
  `value` float NOT NULL COMMENT 'valor de la medicion',
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  KEY `FK_ID_SENSOR_TIPO_idx` (`id_sensor_type`),
  KEY `FK_ID_DISPOSITIVO_idx` (`id_device`),
  CONSTRAINT `FK_ID_DISPOSITIVO` FOREIGN KEY (`id_device`) REFERENCES `ig_devices` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_ID_SENSOR_TIPO` FOREIGN KEY (`id_sensor_type`) REFERENCES `ig_sensors_types` (`id_sensor_type`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_spanish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `erp_mesures`
--

LOCK TABLES `erp_mesures` WRITE;
/*!40000 ALTER TABLE `erp_mesures` DISABLE KEYS */;
/*!40000 ALTER TABLE `erp_mesures` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `erp_sensors_types`
--

DROP TABLE IF EXISTS `erp_sensors_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `erp_sensors_types` (
  `id_sensor_type` int NOT NULL AUTO_INCREMENT,
  `description` varchar(30) COLLATE utf8mb4_spanish_ci NOT NULL,
  PRIMARY KEY (`id_sensor_type`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_spanish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `erp_sensors_types`
--

LOCK TABLES `erp_sensors_types` WRITE;
/*!40000 ALTER TABLE `erp_sensors_types` DISABLE KEYS */;
INSERT INTO `erp_sensors_types` VALUES (1,'gps'),(2,'lcd'),(3,'bt'),(4,'temperatura');
/*!40000 ALTER TABLE `erp_sensors_types` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-04-22 10:50:49
