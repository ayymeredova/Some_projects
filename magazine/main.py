from flask import Flask, request, redirect
from flask.templating import render_template
from flask_sqlalchemy import SQLAlchemy
# from flask_migrate import Migrate

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///shop.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)
# migrate = Migrate(app, db)

class Item(db.Model):
    id = db.Column(db.Integer, primary_key = True)
    title = db.Column(db.String(100), nullable = False )
    price = db.Column(db.Integer, nullable = False)
    isActive = db.Column(db.Boolean, default = True)

    def __repr__(self):
        return self.title


# class CarsModel(db.Model):  
#     __tablename__ = 'cars'


#     id = db.Column(db.Integer, primary_key=True)
#     name = db.Column(db.String())
#     model = db.Column(db.String())
#     doors = db.Column(db.Integer())

#     def __init__(self, name, model, doors):
#         self.name = name
#         self.model = model
#         self.doors = doors



    
@app.route('/')
def index():
    items = Item.query.order_by(Item.price).all()
    return render_template('index.html', data = items)

@app.route('/about')
def about():
    return render_template('about.html')


@app.route('/create', methods = ['POST','GET'])
def create():
    if request.method == "POST":
        title = request.form['title']
        price = request.form['price']

        item = Item(title=title, price= price)

        try:
            db.session.add(item)
            db.session.commit()
            return redirect('/')
        except:
            return "Будьте внимательны и заполните все поля"
    else:
        return render_template('create.html')


if __name__=="__main__":
    app.run(debug = True)




