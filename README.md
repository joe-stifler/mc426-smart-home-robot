# MC426 - SmartHouseRobot

Iremos projetar um software que atualiza em tempo real as informações sobre um robo aspirador de pó, tais como localização do robô na casa, temperatura sendo medida pelo robô, medições de sensores ultrassom, velocidade do robô, etc. Para facilitar a visualização, uma interface 2D representando a planta da casa será mostrada, sendo que o robô irá se movimentar por cima de tal planta. Além do robô, outras informações pertinentes de dispositivos inteligentes será mostrada na planta da casa (tal como sensores de presença, luzes inteligentes, medidores de vasão, etc). O objetivo será oferecer uma visão global do estados dos dispositivos na casa (robô e dispositivos inteligentes) assim como permitir com que o usuário os controle. A princípio, todo o foco da aplicação fará uso de dados simulados para os sensores do robô e dispositivos inteligentes. Contudo futuramente, integrações com dispositivos reais serão vislumbrados.

![Alt text](images/smart_home.png?raw=true "Smart Home APP (QT)")

# Arquitetura do projeto

## Componentes

### Diagrama C4 Conteiners

![Alt text](images/C4_Conteiners.png?raw=true)

### Diagrama C4 Components

![Alt text](images/C4_Components.png?raw=true)

De início, temos uma aplicação mobile e uma aplicação de desktop que fazem chamadas para uma API Gateway, que controla os principais componentes da aplicação.

Nos componentes seguintes, temos: 
- Sign in Controller - Controla e permite que os usuários consigam logar na aplicação.

- Sign Up Controller - Controla e permite que um novo usuário se cadastre.

- Reset Password Controller - Permite que os usuários já cadastrados troquem a senha de login.

- Get Sensor Active Controller - Busca os sensores disponíveis e ativos no sistema.

- Get Sensor Status Controller - Busca o status e atualizações de cada sensor.

- Sensor Component - Permite a visualização dos sensores disponíveis e seus respectivos status.

- Email Component - Envia emails para os usuários(mudança de senha, novidades sobre a aplicação, 'welcome aboard').

- Security Component - Permite que todos os componentes façam procedimentos com segurança.

- Database - Armazena as informações do usuário (login, senha, produtos inteligentes que possui), e as informações dos sensores e seu histórico

- Sensor Wifi Controller - Conecta via wifi todos os produtos inteligentes

