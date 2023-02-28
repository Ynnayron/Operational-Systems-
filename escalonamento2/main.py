import json
import os

QUANTUM = 5

fila = []
prioridades = []

caminho = os.path.abspath("teste.json")

with open(caminho, 'r') as c:
  dados: dict = json.load(c)

#função para verificar se existe mais alguma prioridade do mesmo nivel na fila
def checa_prioridade(fila):
  if (len(fila) >> 1) and (dados[fila[0]][1] == dados[fila[1]][1]):    
    x = fila[0]
    i = fila[1]
    fila[0] = i
    fila[1] = x

  return fila

#for para percorrer o index 1 do valor da chave e adicionar em uma lista ordenada 
for i in dados:
  prioridades.append(dados[i][1])

#ordena a lista do maior pro menor
prioridades.sort(reverse=True)

#for's para percorrer os valores ordenados e os valores do dicionario 
for k in prioridades:
  for j in dados:
    #analisa se a proridade da lista é igual a do processo e se ja esta na fila
    if (dados[j][1] == k) and (j not in fila):
      fila.append(j) #adiciona a chave na fila

print("\nCPU:")

#laço de execução dos processos na CPU
while(fila):
  print("\nFila de processos:", fila, "\n")
  
  print('Processo {} está na CPU'.format(fila[0]))
  for q in range(QUANTUM): #tempo do QUANTUM
    if dados[fila[0]][0] != 0:
      dados[fila[0]][0] -= 1

  print("Processo {} saiu da CPU".format(fila[0]))
  
  if (dados[fila[0]][0] >> 0):
    fila = checa_prioridade(fila)
  else:
    x = fila[0]
    fila.remove(x)
    print("Fim do processo ", x)