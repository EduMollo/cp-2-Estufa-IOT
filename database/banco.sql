-- Banco de dados para monitoramento de estufa IoT
CREATE DATABASE IF NOT EXISTS estufa_iot
  CHARACTER SET utf8mb4
  COLLATE utf8mb4_unicode_ci;

USE estufa_iot;

CREATE TABLE IF NOT EXISTS leituras (
  id           INT          NOT NULL AUTO_INCREMENT,
  temperatura  DECIMAL(5,2) NOT NULL COMMENT 'Temperatura em graus Celsius (DHT22)',
  umidade      DECIMAL(5,2) NOT NULL COMMENT 'Umidade relativa do ar em % (DHT22)',
  luminosidade INT          NOT NULL COMMENT 'Luminosidade aproximada em lux (LDR)',
  criado_em    DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
