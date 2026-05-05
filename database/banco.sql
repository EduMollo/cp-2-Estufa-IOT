CREATE DATABASE IF NOT EXISTS monitoramento_iot;
USE monitoramento_iot;

CREATE TABLE IF NOT EXISTS leituras (
    id INT AUTO_INCREMENT PRIMARY KEY,
    temperatura FLOAT NOT NULL,
    umidade FLOAT NOT NULL,
    luminosidade INT NOT NULL,
    data_hora TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
