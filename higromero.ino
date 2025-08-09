#include <EEPROM.h>

// Definir a porta analógica do higrômetro
const int higrometroPin = A0;

// Valores mínimos e máximos do sensor (ajuste conforme necessário)
const int valorSeco = 1023;  // Valor do sensor quando o solo está completamente seco
const int valorUmido = 0;    // Valor do sensor quando o solo está completamente molhado

// Endereço atual na EEPROM para salvar dados
int enderecoEEPROM = 0;  // Começa na posição 0

void setup() {
  // Inicializar a comunicação serial para monitorar a saída
  Serial.begin(9600);
  Serial.println("Sistema iniciado.");
}

void loop() {
  // Ler o valor analógico do higrômetro
  int leituraSensor = analogRead(higrometroPin);
  
  // Mapear o valor do sensor para a faixa de 0 a 100 (percentual)
  int umidadePercentual = map(leituraSensor, valorSeco, valorUmido, 0, 100);
  
  // Garantir que o valor esteja dentro da faixa correta
  umidadePercentual = constrain(umidadePercentual, 0, 100);
  
  // Exibir a porcentagem de umidade no monitor serial
  Serial.print("Umidade do solo: ");
  Serial.print(umidadePercentual);
  Serial.println("%");

  // Salvar o valor na EEPROM
  EEPROM.write(enderecoEEPROM, umidadePercentual);
  Serial.print("Valor armazenado na EEPROM no endereço: ");
  Serial.println(enderecoEEPROM);

  // Avançar para o próximo endereço
  enderecoEEPROM++;

  // Verificar se o endereço ultrapassou o tamanho da EEPROM
  if (enderecoEEPROM >= EEPROM.length()) {
    Serial.println("EEPROM cheia, reiniciando armazenamento.");
    enderecoEEPROM = 0;  // Voltar ao início
  }

  // Aguardar 1 minuto antes de repetir a leitura
  delay(60000); // 60 segundos
}

