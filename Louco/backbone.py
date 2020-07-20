from flask import Flask, render_template,request,redirect,session,flash,url_for

app = Flask(__name__)

app.secret_key = 'louco'

class Projeto:
    def __init__(self,nome,email,telefone,status):
        self.nome = nome
        self.email = email
        self.telefone = telefone
        self.status = status


projeto1 = Projeto('Conectados','conecta@gmail.com','(81)99563422','1')
projeto2 = Projeto('Flyaway','flay@gmail.com','(81)99826412','1')
projeto3 = Projeto('Avante','avante@gmail.com','(81)9948372','0')
projeto4 = Projeto('Cast','cast@gmail.com','(81)99833312','1')

lista=[projeto1,projeto2,projeto3,projeto4]


@app.route('/')

def index():
    return render_template('h-layout.html',titulo='Projetos',projetos=lista)


@app.route('/novo')

def novo():
    if 'usuario_logado' not in session or session['usuario_logado'] == None:
        return redirect(url_for('login',proxima=url_for('novo')))
    else:    
        return render_template('novo.html',titulo='Novo Projeto',projetos=lista)


@app.route('/criar', methods=['POST',])

def criar():
    nome = request.form['nome']
    email = request.form['email']
    telefone = request.form['telefone']
    status = request.form['status']
    projeto = Projeto(nome,email,telefone,status)
    lista.append(projeto)
    return redirect(url_for('index'))


@app.route('/login')

def login():
    return render_template('/login.html')


@app.route('/autenticar',methods=['POST',])

def autenticar():
    if 'mestra' == request.form['senha']:
        session['usuario_logado'] = request.form['usuario']
        flash("Bem-vindo(a), " + request.form['usuario'])
        proxima_pagina = request.form['proxima']
        return redirect(proxima_pagina)

    else:
        flash("Usuário ou senha invalido(s)")
        return redirect(url_for('login'))


@app.route('/logout')

def logout():
    session['usuario_logado'] = None
    flash('Nenhum usuário logado')
    return redirect(url_for('index'))

app.run(debug=True)