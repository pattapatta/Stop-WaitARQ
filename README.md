Stop-WaitARQ
============

Stop&amp;WaitARQ Server-Client System

N.B.
  Dato che, come avevamo notato, la sola ambiguità che ci può essere in questo tipo di protocollo
  è presente tra un frame ed il suo successivo, in quanto il sender non invierà il frame m prima di aver 
  inviato il frame m-1, la numerazione nell'intestazione dei frame può essere ridotta ad un solo bit, 
  ( aggiungendo la convenzione che il primo frame inviato deve avere il flag settato ad 1 o a 0, ma questo
  lo possiamo decidere noi ). 
  Il reciever a questo punto sa che due frame successivi hanno valori complementari.

Proposte:
  potremmo implementare il sender con dei semafori cosicchè mentre attende l'ack non occupi tempo
  di cpu inutilmente, quindi ci possiamo sbattere dentro qualche tipo di protocollo di sincronizzazione
  
