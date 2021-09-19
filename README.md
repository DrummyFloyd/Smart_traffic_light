# Smart Traffic Light
Smart traffic light est un système de feu de signalisation intelligent. C'est un système embarqué piloté par un microcontrolleur, le STM32F407VG.

## Problématique
Il résoud la problématique de congestion routière dans les centres urbains à cause des chantiers (par exemple dans la ville de Lubumbashi/RDC) et aussi de la croissance du charroi automibile. Le plus grand problème des feux de signalisations traditionnels est qu'ils sont cadancés par une temporisation uniforme et constante, et ne tiennent pas compte de la situation des artères qui affluent vers le carrefour; et permettent par conséquent que sur une voie libre, le feu soit allumé au vert pendant que sur une voie pleine de véhicules, le feu est au rouge; cette situation favorise la congestion routière avec toutes les conséquences qui en découlent. 

## Hypothèse de solution
Smart traffic light permet de résoudre ce problème en arbitrant l'allumage des feux de signalisation selon le dégré de saturation des artères affluent vers le carrefour. Ainsi les voies les plus saturéés auront la priorité sur les voies les plus libres.


## MVP

Pour le MVP, nous avons travaillé sur la carte STM32F407VG émulé, et dans ces condition, nous n'avons qu'un seul bouton utilisateur. Pour simuler le comptage de véhicules dans chaque file de chaque voie, nous allons changer en cas de besoin, telle ou telle autre variable (compteur de véhicule dans la file) pour voir comment le système réagit. Plus tard nous allons créer un code permettant de simuler l'incrémentation/décrémentation aléatoire des files.

### Voici la boucle principale de notre fonction main 
```c
while(1){
		uint8_t currentButton_A_Status = (uint8_t) HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

		if (lastButton_A_Status != currentButton_A_Status && currentButton_A_Status != GPIO_PIN_RESET) {
			++queue_c;
			analyse_queues_situation(&queue_a, &queue_b, &queue_c, &queue_d, priority);
			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			 timer_sleep(BLINK_OFF_TICKS);
		} 
}
```
Nous avons queue_a et queue_b : les deux files de la première voie et queue_c et queue_d : les deux files de la deuxième voie.
Dans le code ci-dessus, en cliquant sur le bouton utilisateur, c'est la file queue_c qu'on incrémente. Si l'on souhaite incrémenter une autre file (par exemple la file queue_a) on doit remplacer l'instruction 
```c
  ++queue_c;
  ```
  par 
  ```c
  ++queue_a;
  ```
  
