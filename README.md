# Projeto de Monitoramento IoT com ESP32, MQTT, Node-RED, MySQL e PokéAPI

## Descrição
Este projeto realiza o monitoramento de uma estufa usando um **ESP32** simulado no **Wokwi**, enviando dados de sensores por **MQTT** para o **Node-RED**.

O Node-RED:
- recebe os dados MQTT
- mostra os valores em gauges e gráficos no dashboard
- salva as leituras em um banco **MySQL**
- consome a **PokéAPI** para exibir informações de um Pokémon no painel

---

## Tecnologias utilizadas
- **ESP32**
- **Wokwi**
- **MQTT / HiveMQ Cloud**
- **Node-RED**
- **Node-RED Dashboard**
- **MySQL**
- **PokéAPI**
- **JSON**

---

## Estrutura do projeto

### Entrada de dados IoT
O ESP32 publica no tópico MQTT:

```text
estufa1/sensores
```

Com payload JSON no formato:

```json
{
  "temperatura": 26.5,
  "umidade": 70.2,
  "luminosidade": 1450
}
```

---

## Fluxo no Node-RED

### 1. Recebimento MQTT
O nó **Sensores MQTT** escuta o tópico:

```text
estufa1/sensores
```

### 2. Conversão JSON
O nó **Converter JSON** transforma a mensagem recebida em objeto JavaScript.

### 3. Separação dos dados
O nó **Separar dados** separa:
- temperatura
- umidade
- luminosidade

Esses valores alimentam:
- gauges
- gráficos históricos

### 4. Inserção no banco
O nó **Insert SQL** gera o comando SQL:

```sql
INSERT INTO leituras (temperatura, umidade, luminosidade) VALUES (...)
```

Depois o nó **Salvar no MySQL** grava no banco de dados.

### 5. Integração com PokéAPI
O fluxo também possui um botão/inject chamado **pokemon**, que consulta a API:

```text
https://pokeapi.co/api/v2/pokemon/Rayquaza
```

Os dados exibidos no dashboard são:
- **Altura do Pokémon**
- **Nome do Pokémon**
- **Tipo do Pokémon**

---

## Dashboard
O dashboard do Node-RED exibe:

### Sensores internos
- Temperatura
- Umidade
- Luminosidade

### Históricos
- Histórico de Temperatura
- Histórico de Umidade
- Histórico de Luminosidade

### Área externa / API
- Altura do Pokémon
- Nome do Pokémon
- Tipo do Pokémon

---

## Configuração do MQTT

### Broker
O fluxo usa o **HiveMQ Cloud** com TLS.

### Tópico
```text
estufa1/sensores
```

---

## Configuração do MySQL

### Banco de dados
Nome do banco:

```text
monitoramento_iot
```

### Tabela necessária
Execute este script no MySQL:

```sql
CREATE DATABASE IF NOT EXISTS monitoramento_iot;
USE monitoramento_iot;

CREATE TABLE IF NOT EXISTS leituras (
    id INT AUTO_INCREMENT PRIMARY KEY,
    temperatura FLOAT NOT NULL,
    umidade FLOAT NOT NULL,
    luminosidade INT NOT NULL,
    data_hora TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### Configuração usada no Node-RED
- **Host:** `127.0.0.1`
- **Porta:** `3306`
- **Database:** `monitoramento_iot`

> É necessário configurar também usuário e senha corretos do MySQL no nó do Node-RED.

---

## API utilizada

### PokéAPI
Endpoint utilizado:

```text
https://pokeapi.co/api/v2/pokemon/Rayquaza
```

Exemplo de informações aproveitadas:
- `height`
- `name`
- `types[0].type.name`

---

## Bibliotecas / módulos do Node-RED
Instale os módulos:

```bash
npm install node-red-dashboard
npm install node-red-node-mysql
```

Ou use o **Manage palette** do Node-RED para instalar:
- `node-red-dashboard`
- `node-red-node-mysql`

---

## Como executar o projeto

### 1. Iniciar o Node-RED
```bash
node-red
```

### 2. Abrir o editor
```text
http://localhost:1880
```

### 3. Abrir o dashboard
```text
http://localhost:1880/ui
```

### 4. Iniciar o MySQL
Certifique-se de que o MySQL está rodando localmente.

### 5. Importar o flow
Importe o arquivo `flows.json` no Node-RED.

### 6. Fazer deploy
Clique em **Deploy**.

---

## Funcionamento esperado
Quando o ESP32/Wokwi publicar dados MQTT:
- os gauges serão atualizados
- os gráficos históricos serão alimentados
- os dados serão gravados no MySQL

Quando o fluxo **pokemon** for executado:
- o dashboard mostrará informações do Pokémon **Rayquaza**

---

## Exemplo de payload MQTT
```json
{
  "temperatura": 25.8,
  "umidade": 68.4,
  "luminosidade": 1320
}
```

---

## Organização do dashboard

### Grupo 1 — Sensores Internos
- Temperatura
- Umidade
- Luminosidade

### Grupo 2 — Históricos
- Histórico Temperatura
- Histórico Umidade
- Histórico Luminosidade

### Grupo 3 — Clima Externo / API
- Altura do Pokémon
- Nome do Pokémon
- Tipo do Pokémon

---

## Observações
- O ESP32 pode ser executado no **Wokwi**
- O MySQL roda localmente no computador
- O Node-RED consome dados reais do broker MQTT
- A PokéAPI foi usada para substituir a API de clima no dashboard

---

## Autores
Eduardo Novaes Mollo | Rm: 561515
Mathaus Victor Marcelino | RM: 564146
Luan Peixoto Marins | RM: 562258
