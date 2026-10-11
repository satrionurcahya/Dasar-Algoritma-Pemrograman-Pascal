# =====================================================
# TUGAS 13.4 - SOAL 1
# jumlah = jumlah + A[i], i = 0..4
# A = {2, 4, 6, 8, 10}
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    A          : .word 2, 4, 6, 8, 10
    pesanJumlah : .asciiz "Jumlah elemen array = "

.text
.globl main

main:
    la   $t0, A         # $t0 = alamat dasar array
    li   $t1, 0         # $t1 = i (indeks) = 0
    li   $t2, 0         # $t2 = jumlah = 0
    li   $t3, 5         # $t3 = batas perulangan (5)

loop:
    # Cek kondisi: i < 5 ?
    bge  $t1, $t3, selesai

    # Hitung alamat A[i]: offset = i * 4
    sll  $t4, $t1, 2    # $t4 = i * 4
    add  $t5, $t0, $t4  # $t5 = alamat A[i]

    # Load A[i]
    lw   $t6, 0($t5)    # $t6 = A[i]

    # jumlah = jumlah + A[i]
    add  $t2, $t2, $t6

    # i++
    addi $t1, $t1, 1

    # Ulang
    j    loop

selesai:
    # Tampilkan hasil
    li   $v0, 4
    la   $a0, pesanJumlah
    syscall

    li   $v0, 1
    move $a0, $t2
    syscall

    li   $v0, 10
    syscall