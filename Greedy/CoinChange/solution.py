
def coin_change(coins: list[int], amount: int):
  """
    Esta función calcula el número mínimo de monedas necesarias 
    para formar una cantidad dada utilizando un algoritmo voraz. 
    Recibe una lista de denominaciones de monedas y una cantidad, 
    y devuelve una lista de tuplas donde cada tupla contiene una 
    denominación de moneda y la cantidad de monedas de esa 
    denominación utilizadas. Si no es posible formar la cantidad 
    con las monedas dadas, devuelve -1.
    
    :param coins: Lista de denominaciones de monedas.
    :param amount: La cantidad objetivo.
    :return: Una lista de tuplas (moneda, cantidad) o -1 si no es 
       posible formar la cantidad con las monedas dadas.
  """
  
  coins.sort(reverse=True)
  result = []
  num_coins = 0
  
  for coin in coins:
    if amount == 0:
      break
    
    num_coins = amount // coin
    amount = amount % coin
    if num_coins > 0:
      result.append((coin, num_coins))

  return result if amount == 0 else -1

coins = [1, 5, 10, 25]
amount = 287
res = coin_change(coins, amount)
if res == -1:
  print("No es posible formar la cantidad con las monedas dadas.")
else: 
  print("Se necesitan las siguientes monedas:")
  for coin, count in res:
    print(f"{count} moneda(s) de {coin}")