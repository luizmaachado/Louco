from flask import Flask, redirect, url_for
from flask import render_template

app = Flask(__name__, static_folder = 'public')

@app.route("/")
def index():
	return render_template('pag_inicial.html')

@app.route("/agendamento")
def agendamento():
	return "<h1>Faça seu agendamento</h1>"	

@app.route("/noticias")
def noticias():
	return "<h1>Veja todas as notícias</h1>"	

@app.route("/projeto")
def cadastro():
	return redirect("http://127.0.0.1:5000/public/cadastro.html")
	
@app.route("/projeto/<name>")
def projeto(name):
	return "<h1>olá {}</h1>".format(name)

@app.route("/add")
def teste():
	return "teste"

if __name__ == '__main__':
	app.run(debug=True)