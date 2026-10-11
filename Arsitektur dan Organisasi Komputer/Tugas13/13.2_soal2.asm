# =====================================================
# TUGAS 13.2 - SOAL 2
# A[2] = A[0] + A[1]
# Array A = {4, 7, 10, 12, 15}
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    A       : .word 4, 7, 10, 12, 15
    pesanA2 : .asciiz "Nilai A[2] setelah update = "

.text
.globl main

main:
    la $t0, A           # $t0 = alamat dasar array A

    # Load A[0] dan A[1]
    lw $t1, 0($t0)      # $t1 = A[0] = 4
    lw $t2, 4($t0)      # $t2 = A[1] = 7

    # Hitung A[0] + A[1]
    add $t3, $t1, $t2   # $t3 = 4 + 7 = 11

    # Simpan ke A[2] (offset 2 * 4 = 8)
    sw $t3, 8($t0)

    # Tampilkan hasil
    li $v0, 4
    la $a0, pesanA2
    syscall

    lw $a0, 8($t0)      # Load nilai A[2] yang baru
    li $v0, 1
    syscall

    li $v0, 10
    syscall