import hashlib
from Cryptodome.Cipher import AES


def hide_lsb(bmp: bytes, data: bytes) -> bytes:
    """
    隐藏数据到图片中
    :param bmp: bmp图片数据
    :param data: 需要隐藏的数据
    :return: 隐藏数据后的图片数据
    """
    hide_data = data
    # 在数据前面加上数据长度, 方便解密时读取数据
    hide_data = len(hide_data).to_bytes(4, byteorder='big') + hide_data

    # print(hide_data)
    # 将数据转换为二进制
    hide_data_bin = ''
    for i in hide_data:
        hide_data_bin += bin(i)[2:].zfill(8)
    # print(hide_data_bin)
    # bmp文件的位图数据
    bmp_data = bmp[54:]
    # 写入数据
    new_bmp_data = []
    for i in range(0, len(hide_data_bin)):
        new_bmp_data.append(bmp_data[i] & 0xFE | int(hide_data_bin[i]))
    new_bmp_data += bmp_data[len(hide_data_bin):]
    return bmp[:54] + bytes(new_bmp_data)


def restore_lsb(bmp: bytes) -> bytes:
    """
    从图片中恢复数据
    :param bmp: bmp图片数据
    :return: 恢复的数据
    """
    bmp_data = bmp[54:]
    # 读取隐藏数据, 格式:[数据长度(4字节), 数据]

    hide_data_bin = ''
    # 读取数据长度
    for i in range(0, 32):
        hide_data_bin += str(bmp_data[i] & 0x01)
    hide_data_len = int(hide_data_bin, 2)
    # 读取数据
    hide_data_bin = ''
    for i in range(32, 32 + hide_data_len * 8):
        hide_data_bin += str(bmp_data[i] & 0x01)
    hide_data = int(hide_data_bin, 2).to_bytes(hide_data_len, byteorder='little')
    hide_data = hide_data[::-1]
    return hide_data


def aes_encrypt(data: bytes, key: bytes) -> bytes:
    """
    加密数据
    :param data: 需要加密的数据
    :param key: 密钥
    :return: 加密后的数据
    """
    # 生成密钥
    key = hashlib.sha256(key).digest()
    # 生成加密器
    aes = AES.new(key, AES.MODE_ECB)
    # 填充数据
    data = data + b'\x00' * (16 - len(data) % 16)
    # 加密数据
    return aes.encrypt(data)


def aes_decrypt(data: bytes, key: bytes) -> bytes:
    """
    解密数据
    :param data: 需要解密的数据
    :param key: 密钥
    :return: 解密后的数据
    """
    # 生成密钥
    key = hashlib.sha256(key).digest()
    # 生成加密器
    aes = AES.new(key, AES.MODE_ECB)
    # 解密数据
    data = aes.decrypt(data)
    # 去除填充数据
    return data.rstrip(b'\x00')
