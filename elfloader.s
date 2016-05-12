
elfloader.img:     file format binary


Disassembly of section .data:

00000000 <.data>:
   0:	8d 4c 24 04          	lea    0x4(%esp),%ecx
   4:	83 e4 f0             	and    $0xfffffff0,%esp
   7:	ff 71 fc             	pushl  -0x4(%ecx)
   a:	55                   	push   %ebp
   b:	89 e5                	mov    %esp,%ebp
   d:	53                   	push   %ebx
   e:	51                   	push   %ecx
   f:	83 ec 10             	sub    $0x10,%esp
  12:	c7 45 f0 00 00 10 00 	movl   $0x100000,-0x10(%ebp)
  19:	8b 45 f0             	mov    -0x10(%ebp),%eax
  1c:	83 ec 04             	sub    $0x4,%esp
  1f:	68 f0 02 00 00       	push   $0x2f0
  24:	6a 10                	push   $0x10
  26:	50                   	push   %eax
  27:	e8 90 00 00 00       	call   0xbc
  2c:	83 c4 10             	add    $0x10,%esp
  2f:	83 ec 08             	sub    $0x8,%esp
  32:	6a 00                	push   $0x0
  34:	68 00 00 10 00       	push   $0x100000
  39:	e8 ae 00 00 00       	call   0xec
  3e:	83 c4 10             	add    $0x10,%esp
  41:	89 45 f4             	mov    %eax,-0xc(%ebp)
  44:	8b 45 f4             	mov    -0xc(%ebp),%eax
  47:	89 c2                	mov    %eax,%edx
  49:	b8 10 00 00 00       	mov    $0x10,%eax
  4e:	89 c3                	mov    %eax,%ebx
  50:	66 53                	push   %bx
  52:	52                   	push   %edx
  53:	cb                   	lret   
  54:	eb d9                	jmp    0x2f
  56:	ba f7 01 00 00       	mov    $0x1f7,%edx
  5b:	ec                   	in     (%dx),%al
  5c:	83 e0 c0             	and    $0xffffffc0,%eax
  5f:	3c 40                	cmp    $0x40,%al
  61:	75 f8                	jne    0x5b
  63:	f3 c3                	repz ret 
  65:	57                   	push   %edi
  66:	53                   	push   %ebx
  67:	8b 5c 24 10          	mov    0x10(%esp),%ebx
  6b:	e8 e6 ff ff ff       	call   0x56
  70:	ba f2 01 00 00       	mov    $0x1f2,%edx
  75:	b8 01 00 00 00       	mov    $0x1,%eax
  7a:	ee                   	out    %al,(%dx)
  7b:	b2 f3                	mov    $0xf3,%dl
  7d:	89 d8                	mov    %ebx,%eax
  7f:	ee                   	out    %al,(%dx)
  80:	89 d8                	mov    %ebx,%eax
  82:	c1 e8 08             	shr    $0x8,%eax
  85:	b2 f4                	mov    $0xf4,%dl
  87:	ee                   	out    %al,(%dx)
  88:	89 d8                	mov    %ebx,%eax
  8a:	c1 e8 10             	shr    $0x10,%eax
  8d:	b2 f5                	mov    $0xf5,%dl
  8f:	ee                   	out    %al,(%dx)
  90:	89 d8                	mov    %ebx,%eax
  92:	c1 e8 18             	shr    $0x18,%eax
  95:	83 c8 e0             	or     $0xffffffe0,%eax
  98:	b2 f6                	mov    $0xf6,%dl
  9a:	ee                   	out    %al,(%dx)
  9b:	b2 f7                	mov    $0xf7,%dl
  9d:	b8 20 00 00 00       	mov    $0x20,%eax
  a2:	ee                   	out    %al,(%dx)
  a3:	e8 ae ff ff ff       	call   0x56
  a8:	8b 7c 24 0c          	mov    0xc(%esp),%edi
  ac:	b9 80 00 00 00       	mov    $0x80,%ecx
  b1:	ba f0 01 00 00       	mov    $0x1f0,%edx
  b6:	fc                   	cld    
  b7:	f2 6d                	repnz insl (%dx),%es:(%edi)
  b9:	5b                   	pop    %ebx
  ba:	5f                   	pop    %edi
  bb:	c3                   	ret    
  bc:	57                   	push   %edi
  bd:	56                   	push   %esi
  be:	53                   	push   %ebx
  bf:	8b 5c 24 14          	mov    0x14(%esp),%ebx
  c3:	8b 7c 24 18          	mov    0x18(%esp),%edi
  c7:	85 ff                	test   %edi,%edi
  c9:	74 1d                	je     0xe8
  cb:	8b 74 24 10          	mov    0x10(%esp),%esi
  cf:	01 df                	add    %ebx,%edi
  d1:	53                   	push   %ebx
  d2:	56                   	push   %esi
  d3:	e8 8d ff ff ff       	call   0x65
  d8:	83 c3 01             	add    $0x1,%ebx
  db:	81 c6 00 02 00 00    	add    $0x200,%esi
  e1:	83 c4 08             	add    $0x8,%esp
  e4:	39 fb                	cmp    %edi,%ebx
  e6:	75 e9                	jne    0xd1
  e8:	5b                   	pop    %ebx
  e9:	5e                   	pop    %esi
  ea:	5f                   	pop    %edi
  eb:	c3                   	ret    
  ec:	55                   	push   %ebp
  ed:	57                   	push   %edi
  ee:	56                   	push   %esi
  ef:	53                   	push   %ebx
  f0:	83 ec 0c             	sub    $0xc,%esp
  f3:	8b 44 24 20          	mov    0x20(%esp),%eax
  f7:	8b 40 18             	mov    0x18(%eax),%eax
  fa:	89 44 24 08          	mov    %eax,0x8(%esp)
  fe:	8b 44 24 20          	mov    0x20(%esp),%eax
 102:	0f b7 40 2c          	movzwl 0x2c(%eax),%eax
 106:	89 44 24 04          	mov    %eax,0x4(%esp)
 10a:	8b 5c 24 20          	mov    0x20(%esp),%ebx
 10e:	89 df                	mov    %ebx,%edi
 110:	03 7b 1c             	add    0x1c(%ebx),%edi
 113:	85 c0                	test   %eax,%eax
 115:	74 5f                	je     0x176
 117:	bd 00 00 00 00       	mov    $0x0,%ebp
 11c:	8b 5f 10             	mov    0x10(%edi),%ebx
 11f:	8b 54 24 24          	mov    0x24(%esp),%edx
 123:	03 57 0c             	add    0xc(%edi),%edx
 126:	8b 74 24 20          	mov    0x20(%esp),%esi
 12a:	03 77 04             	add    0x4(%edi),%esi
 12d:	8b 4f 14             	mov    0x14(%edi),%ecx
 130:	85 db                	test   %ebx,%ebx
 132:	74 1d                	je     0x151
 134:	b8 00 00 00 00       	mov    $0x0,%eax
 139:	89 0c 24             	mov    %ecx,(%esp)
 13c:	83 c2 04             	add    $0x4,%edx
 13f:	8b 0c 30             	mov    (%eax,%esi,1),%ecx
 142:	89 4a fc             	mov    %ecx,-0x4(%edx)
 145:	83 c0 04             	add    $0x4,%eax
 148:	39 c3                	cmp    %eax,%ebx
 14a:	77 f0                	ja     0x13c
 14c:	8b 0c 24             	mov    (%esp),%ecx
 14f:	eb 05                	jmp    0x156
 151:	b8 00 00 00 00       	mov    $0x0,%eax
 156:	39 c1                	cmp    %eax,%ecx
 158:	76 10                	jbe    0x16a
 15a:	29 c2                	sub    %eax,%edx
 15c:	c7 04 02 00 00 00 00 	movl   $0x0,(%edx,%eax,1)
 163:	83 c0 04             	add    $0x4,%eax
 166:	39 c1                	cmp    %eax,%ecx
 168:	77 f2                	ja     0x15c
 16a:	83 c7 20             	add    $0x20,%edi
 16d:	83 c5 01             	add    $0x1,%ebp
 170:	39 6c 24 04          	cmp    %ebp,0x4(%esp)
 174:	75 a6                	jne    0x11c
 176:	8b 44 24 08          	mov    0x8(%esp),%eax
 17a:	83 c4 0c             	add    $0xc,%esp
 17d:	5b                   	pop    %ebx
 17e:	5e                   	pop    %esi
 17f:	5f                   	pop    %edi
 180:	5d                   	pop    %ebp
 181:	c3                   	ret    
 182:	56                   	push   %esi
 183:	53                   	push   %ebx
 184:	83 ec 10             	sub    $0x10,%esp
 187:	8b 74 24 20          	mov    0x20(%esp),%esi
 18b:	8b 54 24 24          	mov    0x24(%esp),%edx
 18f:	8b 44 24 28          	mov    0x28(%esp),%eax
 193:	c6 44 24 0b 92       	movb   $0x92,0xb(%esp)
 198:	c6 44 24 0c 9a       	movb   $0x9a,0xc(%esp)
 19d:	c6 44 24 0d f2       	movb   $0xf2,0xd(%esp)
 1a2:	c6 44 24 0e fa       	movb   $0xfa,0xe(%esp)
 1a7:	c6 44 24 0f 89       	movb   $0x89,0xf(%esp)
 1ac:	8b 5c 24 1c          	mov    0x1c(%esp),%ebx
 1b0:	83 e3 f8             	and    $0xfffffff8,%ebx
 1b3:	8d 8b 00 7e 00 00    	lea    0x7e00(%ebx),%ecx
 1b9:	66 89 83 00 7e 00 00 	mov    %ax,0x7e00(%ebx)
 1c0:	66 89 51 02          	mov    %dx,0x2(%ecx)
 1c4:	89 d3                	mov    %edx,%ebx
 1c6:	c1 eb 10             	shr    $0x10,%ebx
 1c9:	88 59 04             	mov    %bl,0x4(%ecx)
 1cc:	0f b6 5c 34 0b       	movzbl 0xb(%esp,%esi,1),%ebx
 1d1:	88 59 05             	mov    %bl,0x5(%ecx)
 1d4:	83 fe 04             	cmp    $0x4,%esi
 1d7:	74 0e                	je     0x1e7
 1d9:	c1 e8 10             	shr    $0x10,%eax
 1dc:	83 e0 0f             	and    $0xf,%eax
 1df:	83 c8 c0             	or     $0xffffffc0,%eax
 1e2:	88 41 06             	mov    %al,0x6(%ecx)
 1e5:	eb 09                	jmp    0x1f0
 1e7:	c1 e8 10             	shr    $0x10,%eax
 1ea:	83 e0 0f             	and    $0xf,%eax
 1ed:	88 41 06             	mov    %al,0x6(%ecx)
 1f0:	c1 ea 18             	shr    $0x18,%edx
 1f3:	88 51 07             	mov    %dl,0x7(%ecx)
 1f6:	83 c4 10             	add    $0x10,%esp
 1f9:	5b                   	pop    %ebx
 1fa:	5e                   	pop    %esi
 1fb:	c3                   	ret    
 1fc:	8b 54 24 04          	mov    0x4(%esp),%edx
 200:	81 e2 f8 ff 00 00    	and    $0xfff8,%edx
 206:	0f b6 82 07 7e 00 00 	movzbl 0x7e07(%edx),%eax
 20d:	81 c2 00 7e 00 00    	add    $0x7e00,%edx
 213:	c1 e0 18             	shl    $0x18,%eax
 216:	0f b7 52 02          	movzwl 0x2(%edx),%edx
 21a:	09 d0                	or     %edx,%eax
 21c:	c3                   	ret    
