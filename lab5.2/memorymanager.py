from numpy import roll, array

def Buscar(numPagina):
    for n in TLB:
        if n["page"] == numPagina:
            return n["frame"]
    return None

def push(TLB, numPagina, numFrame):
    TLB = roll(TLB, 1)
    TLB[0]["Pagina"] = numPagina
    TLB[0]["Frame"] = numFrame
    return TLB

def leerStorage (numPagina):
    añadirStorage = numPagina*256
    with open("BACKING_STORE.bin", "rb") as archivo:
        archivo.seek(añadirStorage)
        for i in range(256):
            data = archivo.read(1)
            memFisica[Frame*tamañoPag+i] = data

def leerAddressVirtual(filename):
    with open(filename) as archivo:
        addressVirtual = archivo.readlines()
    return [int(x.strip()) for x in addressVirtual]

def ordenar(byte):
        un = ord(byte)
        return un - 256 if un > 127 else un

if __name__ == "__main__":
    filename = "addresses.txt"
    tamañoPag = 256
    numPaginas = 256
    tamaño = 16
    numPagMask = 65280
    pagTabla = [None]*numPaginas
    memFisica = [None]*numPaginas*tamañoPag
    frame = 0
    cont = 0
    TLB = []
    for i in range(tamaño):
        TLB.append({"page":-1, "frame": -1})
    TLB = array(TLB)
    with open("test.txt", "w") as myfile:
        addressesVirtuales = leerAddressVirtual(filename)
        for añadirVirt in addressesVirtuales:
            numPagina = añadirVirt&numPagMask
            numPagina = numPagina>>8
            offset = añadirVirt&255
            Frame = Buscar(numPagina)
            if Frame:
                adressesFis = Frame*256 + offset
                cont = cont + 1
            elif not pagTabla[numPagina]:
                leerStorage(numPagina)
                pagTabla[numPagina] = frame
                TLB = push(TLB, numPagina, frame)
                frame = frame + 1
                adressesFis = pagTabla[numPagina]*256 + offset
            else:
                TLB = push(TLB, numPagina, pagTabla[numPagina])
                adressesFis = pagTabla[numPagina]*256 + offset
            value = memFisica[adressesFis]
            myfile.write("Virtual address: {} Physical address: {} Value: {}\n".format(añadirVirt, adressesFis, ordenar(value)))
