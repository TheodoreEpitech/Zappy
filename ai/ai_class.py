import threading
from random import randint
from tools import is_a_number

class AI:
    def __init__(self, team, net, id=0):
        self.net = net
        self.team = team
        self.lvl = 1
        self.id = id
        self.dead = False
        self.is_elevating = False
        self.last_eject = None

        team_slots_left = net.send_team(team)
        if (team_slots_left == -1):
            self.dead = True
            return
        self.net.logger.info(f"Team {team} has {team_slots_left} slots left", self.id)

    #---------------------------------#
    #           Send and read         #
    #---------------------------------#

    # Return a dictionary of the inventory
    def inventory(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return None
        response = self.net.send_and_read("Inventory", self)
        inventory = None
        while (inventory == None):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return None
                if elem.startswith("["):
                    inventory = response.split("[")[1].split(",")
                else:
                    self.net.add_to_read(elem)
            if inventory == None:
                response = self.net.read(self)
        dic = {}
        for elem in inventory:
            key = elem.split(" ")[1]
            value = int(elem.split(" ")[2])
            dic[key] = value
        return dic
    
    # Look, return a list of the objects around the AI
    def look(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return None
        response = self.net.send_and_read("Look", self)
        look = None
        while (look == None):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return None
                if elem.startswith("["):
                    look = response.split("[")[1].split(",")
                else:
                    self.net.add_to_read(elem)
            if look == None:
                response = self.net.read(self)
        for i in range(len(look)):
            look[i] = look[i].split(" ")
        for elem in look:
            for i in range(len(elem) - 1):
                if elem[i] == "":
                    elem.pop(i)
        look.pop(-1)
        return look
    
    # Fork the AI
    def fork(self, func, args, threads):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        status = False
        response = self.net.send_and_read("Fork", self)
        while (not status):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return
                if elem == "ok":
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status == False:
                response = self.net.read(self)
        self.net.logger.info("Forked", self.id)
        if (not self.net.multi_threading):
            self.net.logger.info("Mutli threading is disabled, manually connect an AI", self.id)
        else:
            threads.append(threading.Thread(target=func, args=args))
            threads[-1].start()

    # Get the nb of unused slots in the team
    def get_unused_slots(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return -1
        response = self.net.send_and_read("Connect_nbr", self).split("\n")
        team_slots_left = -1
        while (team_slots_left == -1):
            for elem in response:
                if elem == "dead":
                    self.dead = True
                    return -1
                if is_a_number(elem):
                    team_slots_left = int(elem)
                else:
                    self.net.add_to_read(elem)
            if team_slots_left == -1:
                response = self.net.read(self)
        self.net.logger.info(f"Team {self.team} has {team_slots_left} slots left", self.id)
        return team_slots_left
    
    # Incantation
    def incantation(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return False
        response = self.net.send_and_read("Incantation", self)
        status = False
        while (not status):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return False
                if elem == "ko":
                    self.net.logger.warning("Failed to incant", self.id)
                    return False
                elif elem == "Elevation underway":
                    self.net.add_to_read(elem)
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status == False:
                response = self.net.read(self)
        self.net.logger.info("Incanted", self.id)
        return True

    # Take an object
    def take(self, obj):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        response = self.net.send_and_read(f"Take {obj}", self)
        status = False
        while (not status and not self.dead):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return False
                if elem == "ko":
                    self.net.logger.warning(f"Failed to take {obj}", self.id)
                    return False
                elif elem == "ok":
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status == False:
                response = self.net.read(self)
        self.net.logger.info(f"Took {obj}", self.id)
        return True
    
    # Take all objects on a tile
    def take_all(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        object_list = self.look()
        if object_list == None:
            return
        object_list = object_list[0]
        for elem in object_list:
            if elem != "player":
                self.take(elem)
    
    def take_all_food(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        object_list = self.look()
        if object_list == None:
            return
        object_list = object_list[0]
        for elem in object_list:
            if elem == "food":
                self.take(elem)

    def get_nb_player_on_tile(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        object_list = self.look()
        if object_list == None:
            return
        object_list = object_list[0]
        nb = 0
        for elem in object_list:
            if elem == "player":
                nb += 1
        return nb
    
    # Drop an object
    def drop(self, obj):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        response = self.net.send_and_read(f"Set {obj}", self)
        status = False
        while (not status):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return False
                if elem == "ko":
                    self.net.logger.warning(f"Failed to drop {obj}", self.id)
                    return False
                elif elem == "ok":
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status == False:
                response = self.net.read(self)
        self.net.logger.info(f"Dropped {obj}", self.id)
        return True

    def drop_all(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        inv = self.inventory()
        if inv == None:
            return
        for key in inv:
            if key != "food":
                for _ in range(inv[key]):
                    self.drop(key)

    def is_inv_empty(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        inv = self.inventory()
        if inv == None:
            return False
        for key in inv:
            if key != "food" and inv[key] > 0:
                return False
        return True
    
    #---------------------------------#
    #        Send without read        #
    #---------------------------------#

    # Move the AI forward
    def forward(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.add_to_send("Forward")
        self.net.logger.info("Moved forward", self.id)
    
    # Turn the AI right
    def turn_right(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.add_to_send("Right")
        self.net.logger.info("Turned right", self.id)

    # Turn the AI left
    def turn_left(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.add_to_send("Left")
        self.net.logger.info("Turned left", self.id)

    def move_random(self):
        random = randint(0, 3)
        match random:
            case 0:
                self.forward()
            case 1:
                self.turn_right()
                self.forward()
            case 2:
                self.turn_left()
                self.forward()

    # Broadcast a message
    def broadcast(self, msg):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.add_to_send(f"Broadcast {msg}")
        self.net.logger.info(f"Broadcasted: {msg}", self.id)
    
    # Eject
    def eject(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.add_to_send("Eject")
        self.net.logger.info("Ejection sended", self.id)
    
    #---------------------------------#
    #        Handle responses         #
    #---------------------------------#

    # Change this function to handle more messages
    def handle_broadcast(self, broadcast_received, k):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        if broadcast_received == "GoGoGadgetIncanto": # Example of broadcast usage
            self.incantation()
